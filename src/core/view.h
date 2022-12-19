

#ifndef VIEW_H
#define VIEW_H


#include "controller.h"
#include "../models/product.h"
#include <memory>

using std::shared_ptr;

namespace Core {
    class Controller;

    class View {
    public:
        View();

    protected:
        Controller* controller;
    };

}

#endif //VIEW_H
