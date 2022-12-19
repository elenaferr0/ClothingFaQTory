

#include "controller.h"
#include <algorithm>

using Controllers::Controller;
using std::transform;
using Views::MainView;

Controller::Controller()
        : hatRepository(HatRepository::getInstance()),
          braceletRepository(BraceletRepository::getInstance()),
          backPackRepository(BackPackRepository::getInstance()),
          vestRepository(VestRepository::getInstance()),
          jeansRepository(JeansRepository::getInstance()),
          overallsRepository(OverallsRepository::getInstance()),
          materialRepository(MaterialRepository::getInstance()),
          sizeRepository(SizeRepository::getInstance()),
          lastError(nullptr),
          view(nullptr) {};

Controller::ProductsMap Controller::findAllProductsByType() {
    ProductsMap map = ProductsMap();

    findProductsOfType(Product::Hat, hatRepository, map);
    findProductsOfType(Product::Bracelet, braceletRepository, map);
    findProductsOfType(Product::BackPack, backPackRepository, map);
    findProductsOfType(Product::Vest, vestRepository, map);
    findProductsOfType(Product::Jeans, jeansRepository, map);
    findProductsOfType(Product::Overalls, overallsRepository, map);
    return map;
}

Controller::MaterialsList Controller::findAllMaterials() {
    Either<Error, MaterialsList> materialsOrError = materialRepository->findAll();

    return materialsOrError.fold<MaterialsList>(
            [&]() { // if left
                lastError = &materialsOrError.forceLeft();
                return MaterialsList();
            },
            [&materialsOrError]() { // if right
                return materialsOrError.forceRight();
            }
    );
}

Controller::SizesList Controller::findAllSizes() {
    Either<Error, SizesList> sizesOrError = sizeRepository->findAll();

    return sizesOrError.fold<SizesList>(
            [&]() { // if left
                lastError = &sizesOrError.forceLeft();
                return SizesList();
            },
            [&sizesOrError]() { // if right
                return sizesOrError.forceRight();
            }
    );
}

Error* Controllers::Controller::getLastError() const {
    return lastError;
}

template<class T>
void Controller::findProductsOfType(Product::ProductType productType,
                                    CRUDRepository<T>* repository,
                                    Controller::ProductsMap& map) {
    if (lastError) {
        return;
    }

    Either<Error, list<shared_ptr<T>>> entitiesOrError = repository->findAll();

    if (entitiesOrError.isRight()) {
        list<shared_ptr<T>> entities = entitiesOrError.forceRight();
        list<shared_ptr<Product>> products(entities.size());

        /* the list wouldn't be implicitly converted to list<shared_ptr<Product>>
           therefore transform is needed. In this situation the observer is also
           registered*/
        transform(entities.begin(),
                  entities.end(),
                  products.begin(),
                  [this](shared_ptr<T> entity) {
                      shared_ptr<Product> product = shared_ptr<Product>(entity);
                      product->registerObserver(view->getProductsView());
                      return product;
                  }
        );
        map.put(productType, products);

    } else {
        map.eraseAll();
        lastError = &entitiesOrError.forceLeft();
    }

}
