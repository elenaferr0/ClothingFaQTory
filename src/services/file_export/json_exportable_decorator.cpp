

#include <QJsonObject>
#include "json_exportable_decorator.h"

using Models::Model;
using Services::FileExport::JSONExportableDecorator;

FieldsGetterVisitor JSONExportableDecorator::fieldsGetterVisitor;

JSONExportableDecorator::JSONExportableDecorator(Model& model)
        : ExportableDecoratorInterface(model) {
    model.accept(fieldsGetterVisitor);
    Map<string, QVariant> fields = fieldsGetterVisitor.getFields();

    for (auto field = fields.cbegin(); field != fields.cend(); field++) {
        QString key = QString::fromStdString((*field).first);
        jsonObject.insert(key, QJsonValue::fromVariant((*field).second));
    }
}

const QJsonObject& Services::FileExport::JSONExportableDecorator::exportData() const {
    return jsonObject;
}

void Services::FileExport::JSONExportableDecorator::accept(VisitorInterface&) {}


