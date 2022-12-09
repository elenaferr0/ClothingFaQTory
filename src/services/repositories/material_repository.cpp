#include "material_repository.h"
#include "../../models/material.h"
#include "../../core/errors/error.h"
#include "../../core/db/expression.h"
#include <list>
#include <QDebug>

using std::list;
using Models::Material;
using Services::MaterialRepository;
using Core::Error;
using Core::Db::Expr;

MaterialRepository::MaterialRepository()
        : Repository("material") {};

Either<Error, Material> MaterialRepository::findById(int id) {
    string sql = queryBuilder.select()
            .from(table)
            .where(Expr("id").equals({"?"}))
            .build();
    QSqlQuery query = exec(sql, QVariant::fromValue<int>(id));
    query.next(); // is needed so the record can be read
    Either<Error, Material> errorOrMaterial = entityMapper.material(query);

    if (errorOrMaterial.isLeft()) {
        qCritical() << QString::fromStdString(
                errorOrMaterial.left().value().getMessage());
    }
    return errorOrMaterial;
}

Either<Error, Material> MaterialRepository::save(Material& entity) {
    // check if that Material already exist
    QSqlDatabase::database().transaction();

    QSqlQuery query;
    string sql;
    list<string> fields = {"name",
                           "cost_per_unit",
                           "unit_of_measure"};

    QVariantList params; // id will later be added only if the entity should be updated
    params << QString::fromStdString(entity.getNameAsString())
           << entity.getCostPerUnit()
           << QString::fromStdString(entity.getUnitOfMeasureAsString());

    if (entity.getId() == -1) { // does not exist => create a new Material
        sql = queryBuilder.insertInto(entity.getTableName(), fields).build();
        query = exec(sql, params);
        query.next();
        entity.setId(query.lastInsertId().toLongLong());
    } else {
        // exists => should update all the fields
        sql = queryBuilder.update(entity.getTableName())
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
        qCritical() << QString::fromStdString(
                hasError.value().getMessage());
        return Either<Error, Material>::ofLeft(hasError.value());
    }

    QSqlDatabase::database().commit();
    return entity;
}

Either<Error, list<Material>> MaterialRepository::saveAll(list<Material>& entities) {
    for (auto en = entities.begin(); en != entities.end(); en++) {
        Either<Error, Material> materialOrError = save(*en);
        if (materialOrError.isLeft()) {
            qCritical() << QString::fromStdString(materialOrError.left().value().getMessage());
            return materialOrError.left().value();
        }

        *en = materialOrError.right().value();
    }
    return entities;
}

optional<Error> MaterialRepository::deleteT(const Material& entity) {
    string sql = queryBuilder.deleteT()
            .from(table)
            .where(Expr("id").equals({"?"}))
            .build();

    QSqlQuery query = exec(sql, QVariant::fromValue<int>(entity.getId()));
    query.next();

    optional<Error> hasError = entityMapper.hasError(query);

    if (hasError.has_value()) {
        qCritical() << QString::fromStdString(
                hasError.value().getMessage());
    }

    return hasError;
}

Either<Error, list<Material>> MaterialRepository::findAll() {
    string sql = queryBuilder.select()
            .from(table)
            .build();
    QSqlQuery query = exec(sql);
    list<Material> materials;
    while (query.next()) {
        Either<Error, Material> materialOrError = entityMapper.material(query);
        if (materialOrError.isLeft()) {
            qCritical() << QString::fromStdString(materialOrError.left().value().getMessage());
            return materialOrError.left().value();
        }
        materials.push_back(materialOrError.right().value());
    }
    return materials;
}
