

#include "hat_mapper.h"

Hat* Services::HatMapper::operator()(const QSqlQuery& query) {
    /*
     * id int
     * code string
     * color string
     * sold_quantity int
     * available_quantity int
     * description string
     * size_id int
     * name string
     * category string
     * is_baseball_cap bool
     */
    checkQuery(query);

    if (lastError) {
        return nullptr;
    }

    QSqlRecord record = query.record();

    return new Hat(record.value("hat.id").toInt(),
                   record.value("hat.code").toString().toStdString(),
                   record.value("hat.color").toString().toStdString(),
                   materialMapper.fromRecord(record),
                   sizeMapper.fromRecord(record),
                   record.value("hat.available_quantity").toInt(),
                   record.value("hat.sold_quantity").toInt(),
                   record.value("hat.description").toString().toStdString(),
                   record.value("hat.category").toString().toStdString(),
                   record.value("hat.is_baseball_hat").toBool());
}
