

#include "controller.h"
#include "view.h"

using Core::Controller;
using Core::View;

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
          view(new View) {}

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

Error* Core::Controller::getLastError() const {
    return lastError;
}

template<class T>
void Controller::findProductsOfType(Product::ProductType productType,
                                    ReadOnlyRepository<T>* repository,
                                    Controller::ProductsMap& map) {
    if (!lastError) {
        Either<Error, list<shared_ptr<T>>> entitiesOrError = repository->findAll();
        if (entitiesOrError.isRight()) {
            list<shared_ptr<Product>> entities = entitiesOrError.forceRight();
            map.put(productType, entities);
        } else {
//            map.eraseAll();
            lastError = &entitiesOrError.forceLeft();
        }
    }
}
