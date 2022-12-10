#include "hat_repository.h"
#include "crud_repository.h"
#include <QSqlRecord>

using Services::HatRepository;

HatRepository* HatRepository::instance;

HatRepository::HatRepository()
        : CRUDRepository("hat") {};


Either<Error, Hat> HatRepository::save(Hat& entity) {
    // check if that hat already exist
    QSqlDatabase::database().transaction();

    QSqlQuery query;
    string sql;
    list<string> fields = {
            "code",
            "color",
            "size_id",
            "available_quantity",
            "sold_quantity",
            "description",
            "category",
            "is_baseball_hat",
            "material_id"
    };

    QVariantList params; // id will later be added only if the entity should be updated
    params << QString::fromStdString(entity.getCode())
           << QString::fromStdString(entity.getColor())
           << entity.getSize().getId()
           << entity.getAvailableQuantity()
           << entity.getSoldQuantity()
           << QString::fromStdString(entity.getDescription())
           << QString::fromStdString(entity.getCategoryAsString())
           << entity.isBaseballCap()
           << entity.getMaterial().getId();

    if (entity.getId() == -1) { // does not exist => create a new Hat
        sql = queryBuilder.insertInto(entity.getTableName(), fields).build();

        query = exec(sql, params);
        query.next();
        entity.setId(query.lastInsertId().toLongLong());
    } else {
        // exists => should update all the fields
        sql = queryBuilder.update("hat")
                .set(fields)
                .where(Expr("id").equals({"?"}))
                .build();

        params << entity.getId();
        query = exec(sql, params);
        query.next();
    }

    optional<Error> hasError = CRUDRepository::hasError(query);

    if (hasError.has_value()) {
        QSqlDatabase::database().rollback();
        qCritical() << QString::fromStdString(hasError.value().getMessage());
        return Either<Error, Hat>::ofLeft(hasError.value());
    }

    QSqlDatabase::database().commit();
    return entity;
}

Either<Error, list<Hat>> HatRepository::saveAll(list<Hat>& entities) {
    for (auto en = entities.begin(); en != entities.end(); en++) {
        Either<Error, Hat> hatOrError = save(*en);
        if (hatOrError.isLeft()) {
            qCritical() << QString::fromStdString(hatOrError.forceLeft().getMessage());
            return hatOrError.forceLeft();
        }

        *en = hatOrError.forceRight();
    }
    return entities;
}

HatRepository* Services::HatRepository::getInstance() {
    if (instance == nullptr) {
        instance = new HatRepository();
    }
    return instance;
}

Either<Error, Hat> Services::HatRepository::findById(int id) {
    return ReadOnlyRepository<Hat>::findById(id, entityMapper.hat);
}

Either<Error, list<Hat>> Services::HatRepository::findAll() {
    return ReadOnlyRepository<Hat>::findAll(entityMapper.hat);
}
