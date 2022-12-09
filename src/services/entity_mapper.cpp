#include "entity_mapper.h"
#include "qvariant.h"

using Services::EntityMapper;
using Models::Product;
using Models::Accessory;
using Models::Accessories::BackPack;
using Models::Accessories::Bracelet;
using Models::Accessories::Hat;
using Models::ClothingItem;
using Models::ClothingItems::Jeans;
using Models::ClothingItems::Overalls;
using Models::ClothingItems::Vest;
using Core::Error;

string toString(const QSqlError::ErrorType& errorType) {
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

Either<Error, QSqlRecord> EntityMapper::checkQuery(const QSqlQuery& query){
  // avoids error checking code duplication
  QSqlError error = query.lastError();

  if (!query.isValid() || error.type() != QSqlError::NoError) { // error occurred
      return Error({toString(error.type()), error.text().toStdString()});
  }

  return query.record();
}

optional <Error> EntityMapper::hasError(QSqlQuery& query) {
    QSqlError error = query.lastError();
    if (error.type() != QSqlError::NoError) {
        return optional<Error>({toString(error.type()),
                                error.text().toStdString()});
    }
    return nullopt;
}

Either <Error, Size> EntityMapper::size(const QSqlQuery& query) {
    /*
	 * id int
	 * name string
	 * extra_percentage_of_material double
	 */
    Either<Error, QSqlRecord> recordOrError = checkQuery(query);

    if(recordOrError.isLeft()){
      return Either<Error, Size>::ofLeft(recordOrError.left().value());
    }

    if (query.size() == 0) {
        return Either<Error, Size>::ofRight(Size());
    }

    QSqlRecord record = recordOrError.right().value();

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
        return recordOrError.left().value();
    }

    if (query.size() == 0) {
        return Material();
    }

    QSqlRecord record = recordOrError.right().value();

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
	return recordOrError.left().value();
    }

    if (query.size() == 0) {
	return Hat();
    }

    QSqlRecord record = recordOrError.right().value();

    return Hat(
	    record.value("id").toInt(),
	    record.value("code").toString().toStdString(),
	    record.value("color").toString().toStdString(),
	    list(0, Material()),
	    size(query).right().value(),
	    record.value("available_quantity").toInt(),
	    record.value("sold_quantity").toInt(),
	    record.value("description").toString().toStdString(),
	    record.value("category").toString().toStdString(),
	    record.value("is_baseball_cap").toBool()
    );
}

//Either<BackPack, Error> EntityMapper::backPack(const QSqlQuery& query) {
//  /*
//     * id int
//     * code string
//     * color string
//     * sold_quantity int
//     * available_quantity int
//     * description string
//     * size_id int
//     * sustainable_materials bool
//     * gender string
//     * name string
//     * category string
//     * capacity string
//     */

//  QSqlError error = query.lastError();
//  if(!query.isValid() || error.isValid()){ // error occurred
//    return Either<BackPack,Error>::ofRight({toString(error.type()),
//					   "Error while getting backpack"});
//  }

//  QSqlRecord record = query.record();

//  BackPack backPack = BackPack(
//	record.value("id").toInt(),
//	record.value("code").toString().toStdString(),
//	record.value("sold_quantity").toInt(),
//	record.value("available_quantity").toInt(),
//	record.value("description").toString().toStdString(),
//	record.value("size_id").toString().toStdString(),
//	record.value("sustainable_materials").toBool(),
//	record.value("gender").toString(),
//	record.value("name").toString(),
//	record.value("category").toString(),
//	record.value("capacity").toString()
//  );
//}

//Accessory EntityMapper::accessory(const QSqlQuery& query) {

//}

//BackPack EntityMapper::backPack(const QSqlQuery& query) {

//}

//Bracelet EntityMapper::bracelet(const QSqlQuery& query) {

//}

//Hat EntityMapper::hat(const QSqlQuery& query) {

//}

//ClothingItem EntityMapper::clothingItem(const QSqlQuery& query) {

//}

//Jeans EntityMapper::jeans(const QSqlQuery& query) {

//}

//Overalls EntityMapper::overalls(const QSqlQuery& query) {

//}

//Vest EntityMapper::vest(const QSqlQuery& query) {

//}
