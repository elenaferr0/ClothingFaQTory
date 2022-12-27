#ifndef EXPORTABLE_DECORATOR_INTERFACE_H
#define EXPORTABLE_DECORATOR_INTERFACE_H

#include "../../models/model.h"

using Models::Model;

namespace Services::FileExport {
    class ExportableDecoratorInterface : public Model {
        public:
            ExportableDecoratorInterface(Model&);

            virtual ~ExportableDecoratorInterface() = default;
    };
}

#endif //EXPORTABLE_DECORATOR_INTERFACE_H
