

#include "main_controller.h"
#include <algorithm>

using std::transform;
using Controllers::MainController;
using Views::MainView;

MainController::MainController(View* view)
        : Controller(view),
          hatRepository(HatRepository::getInstance()),
          sizeRepository(SizeRepository::getInstance()),
          braceletRepository(BraceletRepository::getInstance()),
          backPackRepository(BackPackRepository::getInstance()),
          vestRepository(VestRepository::getInstance()),
          jeansRepository(JeansRepository::getInstance()),
          overallsRepository(OverallsRepository::getInstance()),
          materialRepository(MaterialRepository::getInstance()),
          productRepository(DeleteOnlyRepository::getInstance("product")) {
};

MainController::ProductsMap MainController::findAllProductsByType() {
    ProductsMap map = ProductsMap();

    findProductsOfType(Product::Hat, hatRepository, map);
    findProductsOfType(Product::Bracelet, braceletRepository, map);
    findProductsOfType(Product::BackPack, backPackRepository, map);
    findProductsOfType(Product::Vest, vestRepository, map);
    findProductsOfType(Product::Jeans, jeansRepository, map);
    findProductsOfType(Product::Overalls, overallsRepository, map);

    return map;
}

MainController::MaterialsList MainController::findAllMaterials() {
    Either<Error, MaterialsList> materialsOrError = materialRepository->findAll();

    return materialsOrError.fold<MaterialsList>(
            [&]() { // if left
                emit databaseError(&materialsOrError.forceLeft());
                return MaterialsList();
            },
            [&materialsOrError]() { // if right
                return materialsOrError.forceRight();
            }
    );
}

MainController::SizesList MainController::findAllSizes() {
    Either<Error, SizesList> sizesOrError = sizeRepository->findAll();

    return sizesOrError.fold<SizesList>(
            [&sizesOrError, this]() { // if left
                emit databaseError(&sizesOrError.forceLeft());
                return SizesList();
            },
            [&sizesOrError]() { // if right
                return sizesOrError.forceRight();
            }
    );
}

void Controllers::MainController::deleteProductById(int id) {
    optional<Error> error = productRepository->deleteById(id);
    if (error.has_value()) {
        emit databaseError(&error.value());
    }
}

template<class T>
void MainController::findProductsOfType(Product::ProductType productType,
                                        CRUDRepository<T>* repository,
                                        MainController::ProductsMap& map) {

    Either<Error, LinkedList<T*>> entitiesOrError = repository->findAll();

    entitiesOrError.template fold<void>(
            [&]() {
                map.eraseAll();
                emit databaseError(&entitiesOrError.forceLeft());
            },
            [&, this]() {
                LinkedList<T*> entities = entitiesOrError.forceRight();
                LinkedList<Product*> products;

                /*the list wouldn't be implicitly converted to list<Product*>
                  therefore for_each is needed*/

                std::for_each(entities.begin(),
                              entities.end(),
                              [&products](T* product) {
                                  products.pushBack(product);
                              }
                );
                map.put(productType, products);
            }
    );


}
