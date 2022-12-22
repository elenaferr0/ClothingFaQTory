

#ifndef WIZARD_CONTROLLER_H
#define WIZARD_CONTROLLER_H

#include <QObject>
#include "controller.h"


namespace Controllers {
    class WizardController : public Controller {
        Q_OBJECT
        private:


        public:
            WizardController(View*);
    };
}

#endif //WIZARD_CONTROLLER_H
