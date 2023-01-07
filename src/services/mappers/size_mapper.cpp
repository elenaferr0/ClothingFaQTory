

#include "size_mapper.h"
#include <QVariant>
#include <QDebug>

using Services::SizeMapper;

Size* SizeMapper::operator()(const QSqlQuery& query) {
    /*
	 * id int
	 * name string
	 * extra_percentage_of_material double
	 */
    checkQuery(query);

    if (lastError) {
        return nullptr;
    }

    QSqlRecord record = query.record();

    return new Size(record.value("id").toInt(),
                    record.value("name").toString().toStdString(),
                    record.value("extra_percentage_of_material").toFloat());
}

Size Services::SizeMapper::fromRecord(const QSqlRecord& record) const {
    return Size(record.value("size_id").toInt(),
                record.value("size.name").toString().toStdString(),
                record.value("extra_percentage_of_material").toFloat());
}
