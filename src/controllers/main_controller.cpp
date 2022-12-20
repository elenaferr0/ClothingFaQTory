

#include "main_controller.h"
#include <algorithm>

using std::transform;
using Controllers::MainController;

MainController::MainController(View* view)
        : Controller(view),
          hatRepository(HatRepository::getInstance()),
          braceletRepository(BraceletRepository::getInstance()),
          backPackRepository(BackPackRepository::getInstance()),
          vestRepository(VestRepository::getInstance()),
          jeansRepository(JeansRepository::getInstance()),
          overallsRepository(OverallsRepository::getInstance()),
          materialRepository(MaterialRepository::getInstance()) {
//    connect(this, SIGNAL(databaseError(Error * )), view, SLOT(handleDatabaseError(Error * )));
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


template<class T>
void MainController::findProductsOfType(Product::ProductType productType,
                                        CRUDRepository<T>* repository,
                                        MainController::ProductsMap& map) {

    Either<Error, list<shared_ptr<T>>> entitiesOrError = repository->findAll();

    entitiesOrError.template fold<void>(
            [&]() {
                map.eraseAll();
                emit databaseError(&entitiesOrError.forceLeft());
            },
            [&, this]() {
                list<shared_ptr<T>> entities = entitiesOrError.forceRight();
                list<shared_ptr<Product>> products(entities.size());

                /*the list wouldn't be implicitly converted to list<shared_ptr<Product>>
                  therefore transform is needed. In this situation the observer is also
                  registered*/
                transform(entities.begin(),
                          entities.end(),
                          products.begin(),
                          [this](shared_ptr<T> entity) {
                              shared_ptr<Product> product = shared_ptr<Product>(entity);
//                              product->registerObserver(view->getProductsView());
                              return product;
                          }
                );
                map.put(productType, products);
            }
    );


}
