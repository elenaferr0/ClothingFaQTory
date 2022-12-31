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
#include "../models/clothing_items/vest.h"
#include "../models/clothing_items/overalls.h"
#include <memory>
using Models::Size;
using Models::Product;
using Models::Material;
using Models::Accessory;
using Models::Accessories::BackPack;
using Models::Accessories::Bracelet;
using Models::Accessories::Hat;
using Models::ClothingItem;
using Models::ClothingItems::Overalls;
using Models::ClothingItems::Jeans;
using Models::ClothingItems::Vest;
using Core::Either;
using std::shared_ptr;
using Core::Error;

namespace Services {
    class EntityMapper {
        private:
            static string toString(const QSqlError::ErrorType& errorType);

            static Either<Error, QSqlRecord> checkQuery(const QSqlQuery&);

        public:
            static Either<Error, shared_ptr<Size>> size(const QSqlQuery&);

            static Either<Error, shared_ptr<Material>> material(const QSqlQuery&);

            static Either<Error, shared_ptr<BackPack>> backPack(const QSqlQuery&);

            static Either<Error, shared_ptr<Hat>> hat(const QSqlQuery&);

            static Either<Error, shared_ptr<Vest>> vest(const QSqlQuery&);

            static Either<Error, shared_ptr<Bracelet>> bracelet(const QSqlQuery&);

            static Either<Error, shared_ptr<Jeans>> jeans(const QSqlQuery&);

            static Either<Error, shared_ptr<Overalls>> overalls(const QSqlQuery&);

    };
}

#endif //ENTITY_MAPPER_H
