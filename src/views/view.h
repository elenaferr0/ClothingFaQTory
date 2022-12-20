

#ifndef VIEW_H
#define VIEW_H

#include <QWidget>

namespace Controllers {
    class Controller;
}

using Controllers::Controller;

namespace Views {
    class View {
        protected:
            Controller* controller;
        public:
            View();

            void setController(Controller* controller);

            virtual ~View() = default;
    };
}

#endif //VIEW_H
