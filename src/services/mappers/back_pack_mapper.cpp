

#include "back_pack_mapper.h"

BackPack* Services::BackPackMapper::operator()(const QSqlQuery& query) {
    /*
       * id int
       * code string
       * color string
       * sold_quantity int
       * available_quantity int
       * description string
       * size_id int
       * category string
       * capacity double
       * material_id int
       */

    checkQuery(query);

    if (lastError) {
        return nullptr;
    }

    QSqlRecord record = query.record();

    return new BackPack(record.value("id").toInt(),
                        record.value("code").toString().toStdString(),
                        record.value("color").toString().toStdString(),
                        materialMapper.fromRecord(record),
                        sizeMapper.fromRecord(record),
                        record.value("available_quantity").toInt(),
                        record.value("sold_quantity").toInt(),
                        record.value("description").toString().toStdString(),
                        record.value("category").toString().toStdString(),
                        record.value("capacity").toDouble()
    );
}
