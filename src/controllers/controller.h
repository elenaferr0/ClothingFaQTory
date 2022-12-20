

#ifndef CONTROLLER_H
#define CONTROLLER_H


#include <QObject>
#include "../views/view.h"

namespace Views {
    class View;
}

using Views::View;

namespace Controllers {
    class Controller : public QObject {
        Q_OBJECT
        protected:
            View* view;
        public:
            explicit Controller(View*);

            virtual ~Controller() = default;
    };

}

#endif //CONTROLLER_H
