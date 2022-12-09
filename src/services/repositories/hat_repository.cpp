#include "hat_repository.h"

using Services::HatRepository;

HatRepository::HatRepository()
        : Repository("hat") {};


Either<Error, Hat> HatRepository::findById(int id) {

    string hatSql = queryBuilder.select()
            .from(table)
            .join(QueryBuilder::Join::INNER, "material", Expr("m.id").equals({"h.material_id"}))
            .where(Expr("h.id").equals({"?"}))
            .build();

    string sizeSql = queryBuilder.select("s.*")
            .from(table)
            .join(QueryBuilder::Join::INNER, "size", Expr("s.id").equals({"h.size_id"}))
            .where(Expr("h.id").equals({"?"}))
            .build();

    string materialSql = queryBuilder.select("m.*")
            .from(table)
            .join(QueryBuilder::Join::INNER, "material", Expr("m.id").equals({"h.material_id"}))
            .where(Expr("h.id").equals({"?"}))
            .build();

    // get the hat
    QSqlQuery hatQuery = exec(hatSql, QVariant::fromValue<int>(id));
    hatQuery.next();
    Either<Error, Hat> errorOrHat = entityMapper.hat(hatQuery);

    if (errorOrHat.isLeft()) {
        qCritical() << QString::fromStdString(
                errorOrHat.left().value().getMessage());
        QSqlDatabase::database().rollback();
        return errorOrHat; // return the error
    }

    Hat hat = errorOrHat.right().value();

    // get the size
    QSqlQuery sizeQuery = exec(sizeSql, QVariant::fromValue<int>(id));
    sizeQuery.next();
    Either<Error, Size> errorOrSize = entityMapper.size(sizeQuery);

    if (errorOrSize.isLeft()) {
        qCritical() << QString::fromStdString(
                errorOrSize.left().value().getMessage());
        QSqlDatabase::database().rollback();
        return errorOrSize.left().value(); // return the error
    }

    hat.setSize(errorOrSize.right().value());

    // get the material
    QSqlQuery materialQuery = exec(materialSql, QVariant::fromValue<int>(id));
    materialQuery.next();
    Either<Error, Material> errorOrMaterial = entityMapper.material(materialQuery);

    if (errorOrMaterial.isLeft()) {
        qCritical() << QString::fromStdString(
                errorOrMaterial.left().value().getMessage());
        return errorOrMaterial.left().value(); // return the error
    }

    hat.setMaterial(errorOrMaterial.right().value());
    return hat;
}

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

    optional<Error> hasError = entityMapper.hasError(query);

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
            qCritical() << QString::fromStdString(hatOrError.left().value().getMessage());
            return hatOrError.left().value();
        }

        *en = hatOrError.right().value();
    }
    return entities;
}

optional<Error> HatRepository::deleteT(const Hat& entity) {
    return deleteById(entity.getId());
}

Either<Error, list<Hat>> HatRepository::findAll() {
    string sql = queryBuilder.select()
            .from(table)
            .build();
    QSqlQuery query = exec(sql);
    list<Hat> hats;
    while (query.next()) {
        Either<Error, Hat> hatOrError = entityMapper.hat(query);
        if (hatOrError.isLeft()) {
            qCritical() << QString::fromStdString(hatOrError.left().value().getMessage());
            return hatOrError.left().value();
        }
        hats.push_back(hatOrError.right().value());
    }
    return hats;
}

optional<Error> Services::HatRepository::deleteById(int id) {
    string sql = queryBuilder.deleteT()
            .from(table)
            .where(Expr("id").equals({"?"}))
            .build();

    QSqlQuery query = exec(sql, QVariant::fromValue<int>(id));
    query.next();

    optional<Error> hasError = entityMapper.hasError(query);

    if (hasError.has_value()) {
        qCritical() << QString::fromStdString(
                hasError.value().getMessage());
    }

    return hasError;
}
