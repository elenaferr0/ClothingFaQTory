#include "entity_mapper.h"
#include "repositories/material_repository.h"
#include "repositories/size_repository.h"
#include <QVariant>
#include <memory>

using std::make_shared;
using Services::EntityMapper;

string EntityMapper::toString(const QSqlError::ErrorType& errorType) {
    switch (errorType) {
        case QSqlError::ConnectionError:
            return "Connection Error";
        case QSqlError::StatementError:
            return "Statement Error";
        case QSqlError::TransactionError:
            return "Transaction Error";
        case QSqlError::UnknownError:
            return "Unknown Error";
        default:
            return "";
    }
}

Either<Error, QSqlRecord> EntityMapper::checkQuery(const QSqlQuery& query) {
    // avoids error checking code duplication
    QSqlError error = query.lastError();

    if (!query.isValid() || error.type() != QSqlError::NoError) { // error occurred
        return Error(toString(error.type()), error.text().toStdString());
    }

    return query.record();
}

Either<Error, shared_ptr<Size>> EntityMapper::size(const QSqlQuery& query) {
    /*
	 * id int
	 * name string
	 * extra_percentage_of_material double
	 */
    Either<Error, QSqlRecord> recordOrError = checkQuery(query);

    if (recordOrError.isLeft()) {
        return recordOrError.forceLeft();
    }

    if (query.size() == 0) {
        return make_shared<Size>();
    }

    QSqlRecord record = recordOrError.forceRight();

    return make_shared<Size>(record.value("id").toInt(),
                             record.value("name").toString().toStdString(),
                             record.value("extra_percentage_of_material").toFloat());
}

Either<Error, shared_ptr<Material>> EntityMapper::material(const QSqlQuery& query) {
    /*
     * id int
     * name string
     * unit_of_measure string
     * cost_per_unit double
     */
    Either<Error, QSqlRecord> recordOrError = checkQuery(query);

    if (recordOrError.isLeft()) {
        return recordOrError.forceLeft();
    }

    if (query.size() == 0) {
        return make_shared<Material>();
    }

    QSqlRecord record = recordOrError.forceRight();

    return make_shared<Material>(record.value("id").toInt(),
                                 record.value("name").toString().toStdString(),
                                 record.value("unit_of_measure").toString().toStdString(),
                                 record.value("cost_per_unit").toFloat());
}

Either<Error, shared_ptr<Hat>> EntityMapper::hat(const QSqlQuery& query) {
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
    Either<Error, QSqlRecord> recordOrError = checkQuery(query);

    if (recordOrError.isLeft()) {
        return recordOrError.forceLeft();
    }

    if (query.size() == 0) {
        return make_shared<Hat>();
    }

    QSqlRecord record = recordOrError.forceRight();

    return make_shared<Hat>(record.value("hat.id").toInt(),
                            record.value("hat.code").toString().toStdString(),
                            record.value("hat.color").toString().toStdString(),
                            materialFromRecord(record),
                            sizeFromRecord(record),
                            record.value("hat.available_quantity").toInt(),
                            record.value("hat.sold_quantity").toInt(),
                            record.value("hat.description").toString().toStdString(),
                            record.value("hat.category").toString().toStdString(),
                            record.value("hat.is_baseball_hat").toBool()
    );
}

Either<Error, shared_ptr<Vest>> Services::EntityMapper::vest(const QSqlQuery& query) {
    /*
     * id int
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
     */
    Either<Error, QSqlRecord> recordOrError = checkQuery(query);

    if (recordOrError.isLeft()) {
        return recordOrError.forceLeft();
    }

    if (query.size() == 0) {
        return make_shared<Vest>();
    }

    QSqlRecord record = recordOrError.forceRight();

    return make_shared<Vest>(record.value("id").toInt(),
                             record.value("code").toString().toStdString(),
                             record.value("color").toString().toStdString(),
                             materialFromRecord(record),
                             sizeFromRecord(record),
                             record.value("available_quantity").toInt(),
                             record.value("sold_quantity").toInt(),
                             record.value("description").toString().toStdString(),
                             record.value("sustainable_materials").toBool(),
                             record.value("gender").toString().toStdString(),
                             record.value("has_buttons").toBool()
    );
}

Either<Error, shared_ptr<BackPack>> EntityMapper::backPack(const QSqlQuery& query) {
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

    Either<Error, QSqlRecord> recordOrError = checkQuery(query);

    if (recordOrError.isLeft()) {
        return recordOrError.forceLeft();
    }

    if (query.size() == 0) {
        return make_shared<BackPack>();
    }

    QSqlRecord record = recordOrError.forceRight();

    return make_shared<BackPack>(record.value("id").toInt(),
                                 record.value("code").toString().toStdString(),
                                 record.value("color").toString().toStdString(),
                                 materialFromRecord(record),
                                 sizeFromRecord(record),
                                 record.value("available_quantity").toInt(),
                                 record.value("sold_quantity").toInt(),
                                 record.value("description").toString().toStdString(),
                                 record.value("category").toString().toStdString(),
                                 record.value("capacity").toDouble()
    );
}

Either<Error, shared_ptr<Bracelet>> Services::EntityMapper::bracelet(const QSqlQuery& query) {
    /*
       * id int
       * code string
       * color string
       * sold_quantity int
       * available_quantity int
       * description string
       * size_id int
       * category string
       * pearl_number int
       * pearl_diameter double
       * material_id int
       */

    Either<Error, QSqlRecord> recordOrError = checkQuery(query);

    if (recordOrError.isLeft()) {
        return recordOrError.forceLeft();
    }

    if (query.size() == 0) {
        return make_shared<Bracelet>();
    }

    QSqlRecord record = recordOrError.forceRight();

    return make_shared<Bracelet>(record.value("id").toInt(),
                                 record.value("code").toString().toStdString(),
                                 record.value("color").toString().toStdString(),
                                 materialFromRecord(record),
                                 sizeFromRecord(record),
                                 record.value("available_quantity").toInt(),
                                 record.value("sold_quantity").toInt(),
                                 record.value("description").toString().toStdString(),
                                 record.value("category").toString().toStdString(),
                                 record.value("pearl_number").toInt(),
                                 record.value("pearl_diameter").toDouble()
    );
}

Either<Error, shared_ptr<Jeans>> Services::EntityMapper::jeans(const QSqlQuery& query) {
    /*
       * id int
       * code string
       * color string
       * sold_quantity int
       * available_quantity int
       * description string
       * size_id int
       * sustainable_materials bool
       * gender string
       * material_id int
       * shorts true
       */

    Either<Error, QSqlRecord> recordOrError = checkQuery(query);

    if (recordOrError.isLeft()) {
        return recordOrError.forceLeft();
    }

    if (query.size() == 0) {
        return make_shared<Jeans>();
    }

    QSqlRecord record = recordOrError.forceRight();

    return make_shared<Jeans>(
            record.value("id").toInt(),
            record.value("code").toString().toStdString(),
            record.value("color").toString().toStdString(),
            materialFromRecord(record),
            sizeFromRecord(record),
            record.value("available_quantity").toInt(),
            record.value("sold_quantity").toInt(),
            record.value("description").toString().toStdString(),
            record.value("sustainable_materials").toBool(),
            record.value("gender").toString().toStdString(),
            record.value("shorts").toBool()
    );
}

Either<Error, shared_ptr<Overalls>> Services::EntityMapper::overalls(const QSqlQuery& query) {

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

    Either<Error, QSqlRecord> recordOrError = checkQuery(query);

    if (recordOrError.isLeft()) {
        return recordOrError.forceLeft();
    }

    if (query.size() == 0) {
        return make_shared<Overalls>();
    }

    QSqlRecord record = recordOrError.forceRight();

    return make_shared<Overalls>(record.value("id").toInt(),
                                 record.value("code").toString().toStdString(),
                                 record.value("color").toString().toStdString(),
                                 materialFromRecord(record),
                                 sizeFromRecord(record),
                                 record.value("available_quantity").toInt(),
                                 record.value("sold_quantity").toInt(),
                                 record.value("description").toString().toStdString(),
                                 record.value("sustainable_materials").toBool(),
                                 record.value("gender").toString().toStdString(),
                                 record.value("shorts").toBool(),
                                 record.value("has_buttons").toBool()
    );
}

Material Services::EntityMapper::materialFromRecord(const QSqlRecord& record) {
    return Material(record.value("material_id").toInt(),
                    record.value("material.name").toString().toStdString(),
                    record.value("unit_of_measure").toString().toStdString(),
                    record.value("cost_per_unit").toFloat()
    );
}

Size Services::EntityMapper::sizeFromRecord(const QSqlRecord& record) {
    return Size(record.value("size_id").toInt(),
                record.value("size.name").toString().toStdString(),
                record.value("extra_percentage_of_material").toFloat());
}
