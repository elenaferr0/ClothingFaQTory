

#include "wizard_controller.h"

using Controllers::WizardController;
using Core::Error;
using Core::Either;

WizardController::WizardController(View* view)
        : Controller(view),
          sizeRepository(SizeRepository::getInstance()) {}

WizardController::SizesList WizardController::findAllSizes() {
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