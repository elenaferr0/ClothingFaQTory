

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

MainController::ProductsMap MainController::findAllProductsByType(Filters* filters) {
    ProductsMap map = ProductsMap();

    findAllProductsByTypeHelper(Product::Hat, hatRepository, map, filters);
    findAllProductsByTypeHelper(Product::Bracelet, braceletRepository, map, filters);
    findAllProductsByTypeHelper(Product::BackPack, backPackRepository, map, filters);
    findAllProductsByTypeHelper(Product::Vest, vestRepository, map, filters);
    findAllProductsByTypeHelper(Product::Jeans, jeansRepository, map, filters);
    findAllProductsByTypeHelper(Product::Overalls, overallsRepository, map, filters);

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
void MainController::findAllProductsByTypeHelper(Product::ProductType productType,
                                                 CRUDRepository<T>* repository,
                                                 MainController::ProductsMap& map,
                                                 Filters* filters) {

    Either<Error, LinkedList<shared_ptr<T>>> entitiesOrError = LinkedList<shared_ptr<T>>();

    if (filters) {
        entitiesOrError = repository->findAllWithFilters(*filters);
    } else {
        entitiesOrError = repository->findAll();
    }

    entitiesOrError.template fold<void>(
            [&]() {
                map.eraseAll();
                emit databaseError(&entitiesOrError.forceLeft());
            },
            [&]() {
                LinkedList<shared_ptr<T>> entities = entitiesOrError.forceRight();
                LinkedList<shared_ptr<Product>> products;

                for (auto it = entities.begin(); it != entities.end(); it++) {
                    shared_ptr<Product> product = std::static_pointer_cast<Product>(*it);
                    products.pushBack(product);
                }
                map.put(productType, products);
            }
    );

}

void Controllers::MainController::saveCostPerUnit(shared_ptr<Material> material) {
    Either<Error, shared_ptr<Material>> errorOrMaterial = materialRepository->saveCostPerUnit(material);

    if (errorOrMaterial.isLeft()) {
        emit databaseError(&errorOrMaterial.forceLeft());
    }
}
