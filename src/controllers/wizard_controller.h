

#ifndef WIZARD_CONTROLLER_H
#define WIZARD_CONTROLLER_H

#include <QObject>
#include "controller.h"
#include "../services/repositories/material_repository.h"
#include "../services/repositories/size_repository.h"

using Services::MaterialRepository;
using Services::SizeRepository;

namespace Controllers {
    class WizardController : public Controller {
        Q_OBJECT
        private:
            MaterialRepository* materialRepository;
            SizeRepository* sizeRepository;
        public:
            WizardController(View*);

            shared_ptr<Material> findMaterialByName(const QString&);

            shared_ptr<Size> findSizeByName(const QString&);

    };
}

#endif //WIZARD_CONTROLLER_H
