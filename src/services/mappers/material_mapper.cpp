
#include "material_mapper.h"
#include <QDebug>
using Services::MaterialMapper;

Material* MaterialMapper::operator()(const QSqlQuery& query) {
/*
     * id int
     * name string
     * unit_of_measure string
     * cost_per_unit double
     */
    checkQuery(query);

    if (lastError) {
        return nullptr;
    }

    QSqlRecord record = query.record();

    return new Material(record.value("id").toInt(),
                        record.value("name").toString().toStdString(),
                        record.value("unit_of_measure").toString().toStdString(),
                        record.value("cost_per_unit").toDouble());
}

Material Services::MaterialMapper::fromRecord(const QSqlRecord& record) const {
    return Material(record.value("material_id").toInt(),
                    record.value("material.name").toString().toStdString(),
                    record.value("unit_of_measure").toString().toStdString(),
                    record.value("cost_per_unit").toDouble()
    );
}
