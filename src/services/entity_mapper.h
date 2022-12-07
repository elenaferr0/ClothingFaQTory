#ifndef ENTITY_MAPPER_H
#define ENTITY_MAPPER_H

#include "src/models/product.h"
#include "src/models/accessories/accessory.h"
#include "src/models/accessories/backpack.h"
#include "src/models/accessories/bracelet.h"
#include "src/models/accessories/hat.h"
#include "src/models/clothing_items/clothing_item.h"
#include "src/models/clothing_items/jeans.h"
#include "src/models/clothing_items/overalls.h"
#include "src/models/clothing_items/vest.h"
#include "src/core/errors/error.h"
#include "src/core/errors/either.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

using Models::Size;
using Models::Product;
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
      public:
	static optional<Error> hasError(QSqlQuery&);
	static Either<Error, Size> size(const QSqlQuery&);

//        static Accessory accessory(const QSqlQuery&);

//	static BackPack backPack(const QSqlQuery&);

//        static Bracelet bracelet(const QSqlQuery&);

//        static Hat hat(const QSqlQuery&);

//        static ClothingItem clothingItem(const QSqlQuery&);

//        static Jeans jeans(const QSqlQuery&);

//        static Overalls overalls(const QSqlQuery&);

//        static Vest vest(const QSqlQuery&);

    };
}

#endif //ENTITY_MAPPER_H
