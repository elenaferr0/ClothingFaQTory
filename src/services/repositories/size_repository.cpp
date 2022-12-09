#include "size_repository.h"
#include "../../core/db/expression.h"
#include <list>
#include <QDebug>

using Core::Db::Expr;
using std::list;
using Models::Size;
using Services::SizeRepository;

SizeRepository::SizeRepository()
	: Repository("size") {};


Either <Error, Size> SizeRepository::findById(int id) {
    string sql = queryBuilder.select()
            .from(table)
            .where(Expr("id").equals({"?"}))
            .build();
    QSqlQuery query = exec(sql, QVariant::fromValue<int>(id));
    query.next(); // is needed so the record can be read
    Either <Error, Size> errorOrSize = entityMapper.size(query);

    if (errorOrSize.isLeft()) {
        qCritical() << QString::fromStdString(
                errorOrSize.left().value().getMessage());
    }
    return errorOrSize;
}

Either <Error, Size> SizeRepository::save(Size& entity) {
    // check if that size already exist
    QSqlDatabase::database().transaction();

    QSqlQuery query;
    string sql;
    list <string> fields = {"name", "extra_percentage_of_material"};

    QVariantList params; // id will later be added only if the entity should be updated
    params << QString::fromStdString(entity.getName())
           << entity.getExtraPercentageOfMaterial();

    if (entity.getId() == -1) { // does not exist => create a new Size
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


    optional <Error> hasError = entityMapper.hasError(query);

    if (hasError.has_value()) {
        QSqlDatabase::database().rollback();
        qCritical() << QString::fromStdString(
                hasError.value().getMessage());
        return Either<Error, Size>::ofLeft(hasError.value());
    }

    QSqlDatabase::database().commit();
    return entity;
}

Either <Error, list<Size>> SizeRepository::saveAll(list <Size>& entities) {
    for (auto en = entities.begin(); en != entities.end(); en++) {
        Either <Error, Size> sizeOrError = save(*en);
        if (sizeOrError.isLeft()) {
	    qCritical() << QString::fromStdString(sizeOrError.left().value().getMessage());
	    return sizeOrError.left().value();
        }

        *en = sizeOrError.right().value();
    }
    return entities;
}

optional <Error> SizeRepository::deleteT(const Size& entity) {
    string sql = queryBuilder.deleteT()
            .from(table)
            .where(Expr("id").equals({"?"}))
            .build();

    QSqlQuery query = exec(sql, QVariant::fromValue<int>(entity.getId()));
    query.next();

    optional <Error> hasError = entityMapper.hasError(query);

    if (hasError.has_value()) {
        qCritical() << QString::fromStdString(
                hasError.value().getMessage());
    }

    return hasError;
}

Either <Error, list<Size>> SizeRepository::findAll() {
    string sql = queryBuilder.select()
            .from(table)
            .build();
    QSqlQuery query = exec(sql);
    list <Size> sizes;
    while (query.next()) {
        Either <Error, Size> sizeOrError = entityMapper.size(query);
        if (sizeOrError.isLeft()) {
            qCritical() << QString::fromStdString(sizeOrError.left().value().getMessage());
	    return sizeOrError.left().value();
        }
        sizes.push_back(sizeOrError.right().value());
    }
    return sizes;
}
