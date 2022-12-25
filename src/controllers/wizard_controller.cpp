

#include "wizard_controller.h"

using Controllers::WizardController;
using Core::Error;

WizardController::WizardController(View* view)
        : Controller(view),
          hatRepository(HatRepository::getInstance()),
          sizeRepository(SizeRepository::getInstance()),
          braceletRepository(BraceletRepository::getInstance()),
          backPackRepository(BackPackRepository::getInstance()),
          vestRepository(VestRepository::getInstance()),
          jeansRepository(JeansRepository::getInstance()),
          overallsRepository(OverallsRepository::getInstance()),
          materialRepository(MaterialRepository::getInstance()) {}

Material* WizardController::findMaterialById(int id) {
    Either<Error, Material*> errorOrMaterial = materialRepository->findById(id);

    return errorOrMaterial.fold<Material*>(
            [&]() {
                emit databaseError(&errorOrMaterial.forceLeft());
                return nullptr;
            },
            [&errorOrMaterial]() {
                return errorOrMaterial.forceRight();
            }
    );
}

Size* WizardController::findSizeById(int id) {
    Either<Error, Size*> errorOrSize = sizeRepository->findById(id);

    return errorOrSize.fold<Size*>(
            [&]() {
                emit databaseError(&errorOrSize.forceLeft());
                return nullptr;
            },
            [&errorOrSize]() {
                return errorOrSize.forceRight();
            }
    );
}

void Controllers::WizardController::save(Jeans* jeans) {
    Either<Error, Jeans*> errorOrJeans = jeansRepository->save(jeans);
    if (errorOrJeans.isLeft()) {
        emit databaseError(&errorOrJeans.forceLeft());
    }
}

void Controllers::WizardController::save(Hat* hat) {
    Either<Error, Hat*> hatOrError = hatRepository->save(hat);
    if (hatOrError.isLeft()) {
        emit databaseError(&hatOrError.forceLeft());
    }
}

void Controllers::WizardController::save(Vest* vest) {
    Either<Error, Vest*> vestOrError = vestRepository->save(vest);
    if (vestOrError.isLeft()) {
        emit databaseError(&vestOrError.forceLeft());
    }
}

void Controllers::WizardController::save(Bracelet* bracelet) {
    Either<Error, Bracelet*> braceletOrError = braceletRepository->save(bracelet);
    if (braceletOrError.isLeft()) {
        emit databaseError(&braceletOrError.forceLeft());
    }
}

void Controllers::WizardController::save(BackPack* backPack) {
    Either<Error, BackPack*> backPackOrError = backPackRepository->save(backPack);
    if (backPackOrError.isLeft()) {
        emit databaseError(&backPackOrError.forceLeft());
    }
}

void Controllers::WizardController::save(Overalls* overalls) {
    Either<Error, Overalls*> errorOrOveralls = overallsRepository->save(overalls);
    if (errorOrOveralls.isLeft()) {
        emit databaseError(&errorOrOveralls.forceLeft());
    }
}

void WizardController::handleProductCreation(Product* product, Product::ProductType productType) {
    switch (productType) {
        case Models::Product::Jeans:
            save(dynamic_cast<Jeans*>(product));
            break;
        case Models::Product::Vest:
            save(dynamic_cast<Vest*>(product));
            break;
        case Models::Product::Overalls:
            save(dynamic_cast<Overalls*>(product));
            break;
        case Models::Product::BackPack:
            save(dynamic_cast<BackPack*>(product));
            break;
        case Models::Product::Bracelet:
            save(dynamic_cast<Bracelet*>(product));
            break;
        case Models::Product::Hat:
            save(dynamic_cast<Hat*>(product));
            break;
    }
}

void Controllers::WizardController::handleProductEditing(Product* product, Product::ProductType productType) {

}
