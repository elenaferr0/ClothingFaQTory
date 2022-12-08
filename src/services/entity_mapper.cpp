#include "entity_mapper.h"
#include "qvariant.h"
#include "src/core/errors/error.h"
#include "src/core/errors/either.h"

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

    QSqlError error = query.lastError();

    if (!query.isValid() || error.type() != QSqlError::NoError) { // error occurred
        return Either<Error, Size>::ofLeft({toString(error.type()),
                                            error.text().toStdString()});
    }

    QSqlRecord record = query.record();

    if (query.size() == 0) {
        return Either<Error, Size>::ofRight(Size());
    }

    return Either<Error, Size>::ofRight(
            Size(
                    record.value("id").toInt(),
                    record.value("name").toString().toStdString(),
                    record.value("extra_percentage_of_material").toFloat()
            )
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