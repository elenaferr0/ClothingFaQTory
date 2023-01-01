

#include "wizard_controller.h"
#include <memory>

using std::make_shared;
using std::dynamic_pointer_cast;
using Controllers::WizardController;
using Core::Error;

WizardController::WizardController(View* view)
        : Controller(view),
          materialRepository(MaterialRepository::getInstance()),
          sizeRepository(SizeRepository::getInstance()),
          hatRepository(HatRepository::getInstance()),
          braceletRepository(BraceletRepository::getInstance()),
          backPackRepository(BackPackRepository::getInstance()),
          vestRepository(VestRepository::getInstance()),
          jeansRepository(JeansRepository::getInstance()),
          overallsRepository(OverallsRepository::getInstance()) {}

shared_ptr<Material> WizardController::findMaterialById(int id) {
    Either<Error, shared_ptr<Material>> errorOrMaterial = materialRepository->findById(id);

    return errorOrMaterial.fold<shared_ptr<Material>>(
            [&]() {
                emit databaseError(&errorOrMaterial.forceLeft());
                return nullptr;
            },
            [&errorOrMaterial]() {
                return errorOrMaterial.forceRight();
            }
    );
}

shared_ptr<Size> WizardController::findSizeById(int id) {
    Either<Error, shared_ptr<Size>> errorOrSize = sizeRepository->findById(id);

    return errorOrSize.fold<shared_ptr<Size>>(
            [&]() {
                emit databaseError(&errorOrSize.forceLeft());
                return nullptr;
            },
            [&errorOrSize]() {
                return errorOrSize.forceRight();
            }
    );
}

void Controllers::WizardController::save(shared_ptr<Jeans> jeans) {
    Either<Error, shared_ptr<Jeans>> errorOrJeans = jeansRepository->save(jeans);
    if (errorOrJeans.isLeft()) {
        emit databaseError(&errorOrJeans.forceLeft());
    }
}

void Controllers::WizardController::save(shared_ptr<Hat> hat) {
    Either<Error, shared_ptr<Hat>> hatOrError = hatRepository->save(hat);
    if (hatOrError.isLeft()) {
        emit databaseError(&hatOrError.forceLeft());
    }
}

void Controllers::WizardController::save(shared_ptr<Vest> vest) {
    Either<Error, shared_ptr<Vest>> vestOrError = vestRepository->save(vest);
    if (vestOrError.isLeft()) {
        emit databaseError(&vestOrError.forceLeft());
    }
}

void Controllers::WizardController::save(shared_ptr<Bracelet> bracelet) {
    Either<Error, shared_ptr<Bracelet>> braceletOrError = braceletRepository->save(bracelet);
    if (braceletOrError.isLeft()) {
        emit databaseError(&braceletOrError.forceLeft());
    }
}

void Controllers::WizardController::save(shared_ptr<BackPack> backPack) {
    Either<Error, shared_ptr<BackPack>> backPackOrError = backPackRepository->save(backPack);
    if (backPackOrError.isLeft()) {
        emit databaseError(&backPackOrError.forceLeft());
    }
}

void Controllers::WizardController::save(shared_ptr<Overalls> overalls) {
    Either<Error, shared_ptr<Overalls>> errorOrOveralls = overallsRepository->save(overalls);
    if (errorOrOveralls.isLeft()) {
        emit databaseError(&errorOrOveralls.forceLeft());
    }
}

void WizardController::handleProductEditAndCreate(shared_ptr<Product> product, Product::ProductType productType) {
    switch (productType) {
        case Models::Product::Jeans: {
            shared_ptr<Jeans> jeans = dynamic_pointer_cast<Jeans>(product);
            save(jeans);
            return;
        }
        case Models::Product::Vest: {
            shared_ptr<Vest> vest = dynamic_pointer_cast<Vest>(product);
            save(vest);
            return;
        }
        case Models::Product::Overalls: {
            shared_ptr<Overalls> overalls = dynamic_pointer_cast<Overalls>(product);
            save(overalls);
            return;
        }
        case Models::Product::BackPack: {
            shared_ptr<BackPack> backPack = dynamic_pointer_cast<BackPack>(product);
            save(backPack);
            return;
        }
        case Models::Product::Bracelet: {
            shared_ptr<Bracelet> bracelet = dynamic_pointer_cast<Bracelet>(product);
            save(bracelet);
            return;
        }
        case Models::Product::Hat: {
            shared_ptr<Hat> hat = dynamic_pointer_cast<Hat>(product);
            save(hat);
            return;
        }
    }
}
