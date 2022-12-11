#include "entity_mapper.h"
#include "qvariant.h"

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
        return Error({toString(error.type()), error.text().toStdString()});
    }

    return query.record();
}

optional<Error> EntityMapper::hasError(QSqlQuery& query) {
    QSqlError error = query.lastError();
    if (error.type() != QSqlError::NoError) {
        return optional<Error>({toString(error.type()),
                                error.text().toStdString()});
    }
    return nullopt;
}

Either<Error, Size> EntityMapper::size(const QSqlQuery& query) {
    /*
	 * id int
	 * name string
	 * extra_percentage_of_material double
	 */
    Either<Error, QSqlRecord> recordOrError = checkQuery(query);

    if (recordOrError.isLeft()) {
        return Either<Error, Size>::ofLeft(recordOrError.forceLeft());
    }

    if (query.size() == 0) {
        return Either<Error, Size>::ofRight(Size());
    }

    QSqlRecord record = recordOrError.forceRight();

    return Size(record.value("id").toInt(),
                record.value("name").toString().toStdString(),
                record.value("extra_percentage_of_material").toFloat());
}

Either<Error, Material> EntityMapper::material(const QSqlQuery& query) {
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
        return Material();
    }

    QSqlRecord record = recordOrError.forceRight();

    return Material(
            record.value("id").toInt(),
            record.value("name").toString().toStdString(),
            record.value("unit_of_measure").toString().toStdString(),
            record.value("cost_per_unit").toFloat()
    );
}

Either<Error, Hat> EntityMapper::hat(const QSqlQuery& query) {
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
        return Hat();
    }

    QSqlRecord record = recordOrError.forceRight();

    return Hat(
            record.value("id").toInt(),
            record.value("code").toString().toStdString(),
            record.value("color").toString().toStdString(),
            Material(),
            Size(),
            record.value("available_quantity").toInt(),
            record.value("sold_quantity").toInt(),
            record.value("description").toString().toStdString(),
            record.value("category").toString().toStdString(),
            record.value("is_baseball_hat").toBool()
    );
}

Either<Error, Vest> Services::EntityMapper::vest(const QSqlQuery& query) {
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
        return Vest();
    }

    QSqlRecord record = recordOrError.forceRight();

    return Vest(
            record.value("id").toInt(),
            record.value("code").toString().toStdString(),
            record.value("color").toString().toStdString(),
            Material(),
            Size(),
            record.value("available_quantity").toInt(),
            record.value("sold_quantity").toInt(),
            record.value("description").toString().toStdString(),
            record.value("sustainable_materials").toBool(),
            record.value("gender").toString().toStdString(),
            record.value("has_buttons").toBool()
    );
}

Either<Error, BackPack> EntityMapper::backPack(const QSqlQuery& query) {
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
        return BackPack();
    }

    QSqlRecord record = recordOrError.forceRight();

    return BackPack(
            record.value("id").toInt(),
            record.value("code").toString().toStdString(),
            record.value("color").toString().toStdString(),
            Material(),
            Size(),
            record.value("available_quantity").toInt(),
            record.value("sold_quantity").toInt(),
            record.value("description").toString().toStdString(),
            record.value("category").toString().toStdString(),
            record.value("capacity").toDouble()
    );
}

Either<Error, Bracelet> Services::EntityMapper::bracelet(const QSqlQuery& query) {
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
        return Bracelet();
    }

    QSqlRecord record = recordOrError.forceRight();

    return Bracelet(
            record.value("id").toInt(),
            record.value("code").toString().toStdString(),
            record.value("color").toString().toStdString(),
            Material(),
            Size(),
            record.value("available_quantity").toInt(),
            record.value("sold_quantity").toInt(),
            record.value("description").toString().toStdString(),
            record.value("category").toString().toStdString(),
            record.value("pearl_number").toInt(),
            record.value("pearl_diameter").toDouble()
    );
}

Either<Error, Jeans> Services::EntityMapper::jeans(const QSqlQuery& query) {
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
        return Jeans();
    }

    QSqlRecord record = recordOrError.forceRight();

    return Jeans(
            record.value("id").toInt(),
            record.value("code").toString().toStdString(),
            record.value("color").toString().toStdString(),
            Material(),
            Size(),
            record.value("available_quantity").toInt(),
            record.value("sold_quantity").toInt(),
            record.value("description").toString().toStdString(),
            record.value("sustainable_materials").toBool(),
            record.value("gender").toString().toStdString(),
            record.value("shorts").toBool()
    );
}

Either<Error, Overalls> Services::EntityMapper::overalls(const QSqlQuery& query) {

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
        return Overalls();
    }

    QSqlRecord record = recordOrError.forceRight();

    return Overalls(
            record.value("id").toInt(),
            record.value("code").toString().toStdString(),
            record.value("color").toString().toStdString(),
            Material(),
            Size(),
            record.value("available_quantity").toInt(),
            record.value("sold_quantity").toInt(),
            record.value("description").toString().toStdString(),
            record.value("sustainable_materials").toBool(),
            record.value("gender").toString().toStdString(),
            record.value("shorts").toBool(),
            record.value("has_buttons").toBool()
    );
}
