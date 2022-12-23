

#include "wizard_controller.h"

using Controllers::WizardController;
using Core::Error;

WizardController::WizardController(View* view)
        : Controller(view),
          materialRepository(MaterialRepository::getInstance()),
          sizeRepository(SizeRepository::getInstance()) {}

shared_ptr<Material> Controllers::WizardController::findMaterialByName(const QString& name) {
    Either<Error, shared_ptr<Material>> errorOrMaterial = materialRepository->findByName(
            Material::namefromString(name.toStdString()));

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

shared_ptr<Size> Controllers::WizardController::findSizeByName(const QString& name) {
    Either<Error, shared_ptr<Size>> errorOrSize = sizeRepository->findByName(
            Size::nameFromString(name.toStdString()));

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

