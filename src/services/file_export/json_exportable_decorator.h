

#ifndef JSON_EXPORTER_DECORATOR_H
#define JSON_EXPORTER_DECORATOR_H

#include <QJsonDocument>
#include "../../models/fields_getter_visitor.h"
#include "../../models/model.h"
#include "exportable_decorator_interface.h"

using Models::FieldsGetterVisitor;
using Models::Model;

namespace Services::FileExport {
    class JSONExportableDecorator : public ExportableDecoratorInterface {
        private:
            static FieldsGetterVisitor fieldsGetterVisitor;
            QJsonObject jsonObject;

            // overriding accept is necessary to make JSONExportableDecorator concrete
            void accept(VisitorInterface& visitor) override;

        public:
            explicit JSONExportableDecorator(Model&);

            const QJsonObject& exportData() const;

    };
}


#endif //JSON_EXPORTER_DECORATOR_H
