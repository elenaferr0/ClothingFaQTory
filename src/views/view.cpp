

#include "view.h"

using Views::View;

View::View() {

}

void View::setController(Controller* controller) {
    this->controller = controller;
}

Controller* Views::View::getController() const {
    return controller;
}
