#ifndef ENTITY_MAPPER_H
#define ENTITY_MAPPER_H

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include "../core/errors/either.h"
#include "../core/errors/error.h"
#include "../models/size.h"
#include "../models/size.h"
#include "../models/accessories/backpack.h"
#include "../models/accessories/bracelet.h"
#include "../models/accessories/hat.h"
#include "../models/clothing_items/jeans.h"
#include "../models/clothing_items/overalls.h"
#include "../models/clothing_items/vest.h"

using Models::Size;
using Models::Product;
using Models::Material;
using Models::Accessory;
using Models::Accessories::BackPack;
using Models::Accessories::Bracelet;
using Models::Accessories::Hat;
using Models::ClothingItem;
using Models::ClothingItems::Jeans;
using Models::ClothingItems::Overalls;
using Models::ClothingItems::Vest;
using Core::Either;
using Core::Error;

namespace Services {
    class EntityMapper {
    private:
        static string errorType(const QSqlError::ErrorType& errorType);

        static Either<Error, QSqlRecord> checkQuery(const QSqlQuery&);

    public:
        static optional<Error> hasError(QSqlQuery&);

        static Either<Error, Size> size(const QSqlQuery&);

        static Either<Error, Material> material(const QSqlQuery&);

//        static Accessory accessory(const QSqlQuery&);

//	static BackPack backPack(const QSqlQuery&);

//        static Bracelet bracelet(const QSqlQuery&);

        static Either<Error, Hat> hat(const QSqlQuery&);

//        static ClothingItem clothingItem(const QSqlQuery&);

//        static Jeans jeans(const QSqlQuery&);

//        static Overalls overalls(const QSqlQuery&);

//        static Vest vest(const QSqlQuery&);

    };
}

#endif //ENTITY_MAPPER_H
