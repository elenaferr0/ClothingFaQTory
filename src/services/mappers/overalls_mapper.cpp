

#include "overalls_mapper.h"

namespace Services {
    Overalls* OverallsMapper::operator()(const QSqlQuery& query) {

        /* id int
        * code string
        * color string
        * sold_quantity int
        * available_quantity int
        * description string
        * size_id int
        * sustainable_materials bool
        * gender string
        * material_id int
        * has_buttons bool
        * shorts bool
        */

        checkQuery(query);

        if (lastError) {
            return nullptr;
        }

        QSqlRecord record = query.record();

        return new Overalls(record.value("id").toInt(),
                            record.value("code").toString().toStdString(),
                            record.value("color").toString().toStdString(),
                            materialMapper.fromRecord(record),
                            sizeMapper.fromRecord(record),
                            record.value("available_quantity").toInt(),
                            record.value("sold_quantity").toInt(),
                            record.value("description").toString().toStdString(),
                            record.value("sustainable_materials").toBool(),
                            record.value("gender").toString().toStdString(),
                            record.value("shorts").toBool(),
                            record.value("has_buttons").toBool()
        );
    }
} // Services