#ifndef DECORATOR_INTERFACE_H
#define DECORATOR_INTERFACE_H

#include "../../models/model.h"

using Models::Model;

namespace Services::FileExport {
    class DecoratorInterface : public Model {
        public:
            DecoratorInterface(Model&);

            virtual ~DecoratorInterface() = default;
    };
}

#endif //DECORATOR_INTERFACE_H
