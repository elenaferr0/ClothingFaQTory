

#ifndef WIZARD_CONTROLLER_H
#define WIZARD_CONTROLLER_H

#include <QObject>
#include "controller.h"
#include "../services/repositories/size_repository.h"

using Services::SizeRepository;

namespace Controllers {
    class WizardController : public Controller {
        Q_OBJECT
            typedef list<shared_ptr<Size>> SizesList;
        private:
            SizeRepository* sizeRepository;

        public:
            WizardController(View*);

            SizesList findAllSizes();
    };
}

#endif //WIZARD_CONTROLLER_H
