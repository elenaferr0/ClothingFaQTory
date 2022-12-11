#ifndef CRUD_REPOSITORY_H
#define CRUD_REPOSITORY_H

#include "readonly_repository.h"
#include "../../core/errors/error.h"
#include "../../core/errors/either.h"
#include "../../models/size.h"
#include "../../models/material.h"
#include <functional>

using std::function;
using Services::ReadOnlyRepository;
using Core::Error;
using Core::Either;
using Models::Size;
using Models::Material;

namespace Services {
    template<class T>
    class CRUDRepository : public ReadOnlyRepository<T> {
    public:
        CRUDRepository(const string& table, function<Either<Error, T>(const QSqlQuery&)> mappingFunction)
                : ReadOnlyRepository<T>(table, mappingFunction) {};

        virtual Either<Error, T> save(T& entity) = 0;

        Either<Error, list<T>> saveAll(list<T>& entities);

        optional<Error> deleteT(const T& entity);

        optional<Error> deleteById(int id);

        Either<Error, T> findById(int id) override;

        Either<Error, list<T>> findAll() override;

    };

    template<class T>
    Either<Error, list<T>> CRUDRepository<T>::saveAll(list<T>& entities) {
        for (auto en = entities.begin(); en != entities.end(); en++) {
            Either<Error, T> entityOrError = save(*en);
            if (entityOrError.isLeft()) {
                qCritical() << QString::fromStdString(entityOrError.forceLeft().getMessage());
                return entityOrError.forceLeft();
            }

            *en = entityOrError.forceRight();
        }
        return entities;
    }

    template<class T>
    Either<Error, T> CRUDRepository<T>::findById(int id) {
        string mainEntitySql = ReadOnlyRepository<T>::queryBuilder.select()
                .from(ReadOnlyRepository<T>::table)
                .where(Expr("h.id").equals({"?"}))
                .build();

        string sizeSql = ReadOnlyRepository<T>::queryBuilder.select("s.*")
                .from(ReadOnlyRepository<T>::table)
                .join(QueryBuilder::Join::INNER, "size", Expr("s.id").equals({"h.size_id"}))
                .where(Expr("h.id").equals({"?"}))
                .build();

        string materialSql = ReadOnlyRepository<T>::queryBuilder.select("m.*")
                .from(ReadOnlyRepository<T>::table)
                .join(QueryBuilder::Join::INNER, "material", Expr("m.id").equals({"h.material_id"}))
                .where(Expr("h.id").equals({"?"}))
                .build();

        // get the entity
        QSqlQuery mainEntityQuery = ReadOnlyRepository<T>::exec(mainEntitySql, QVariant::fromValue<int>(id));
        mainEntityQuery.next();
        Either<Error, T> errorOrEntity = ReadOnlyRepository<T>::mappingFunction(mainEntityQuery);

        if (errorOrEntity.isLeft()) {
            qCritical() << QString::fromStdString(
                    errorOrEntity.forceLeft().getMessage());
            QSqlDatabase::database().rollback();
            return errorOrEntity; // return the error
        }

        // get the size
        QSqlQuery sizeQuery = ReadOnlyRepository<T>::exec(sizeSql, QVariant::fromValue<int>(id));
        sizeQuery.next();
        Either<Error, Size> errorOrSize = ReadOnlyRepository<T>::entityMapper.size(sizeQuery);

        if (errorOrSize.isLeft()) {
            qCritical() << QString::fromStdString(
                    errorOrSize.forceLeft().getMessage());
            QSqlDatabase::database().rollback();
            return errorOrSize.forceLeft(); // return the error
        }

        errorOrEntity.forceRight().setSize(errorOrSize.forceRight());

        // get the material
        QSqlQuery materialQuery = ReadOnlyRepository<T>::exec(materialSql, QVariant::fromValue<int>(id));
        materialQuery.next();
        Either<Error, Material> errorOrMaterial = ReadOnlyRepository<T>::entityMapper.material(materialQuery);

        if (errorOrMaterial.isLeft()) {
            qCritical() << QString::fromStdString(
                    errorOrMaterial.forceLeft().getMessage());
            return errorOrMaterial.forceLeft(); // return the error
        }

        errorOrEntity.forceRight().setMaterial(errorOrMaterial.forceRight());
        return errorOrEntity.forceRight();
    }

    template<class T>
    Either<Error, list<T>> CRUDRepository<T>::findAll() {
        string sql = ReadOnlyRepository<T>::queryBuilder.select()
                .from(ReadOnlyRepository<T>::table)
                .build();
        QSqlQuery query = ReadOnlyRepository<T>::exec(sql);
        list<T> entities;
        while (query.next()) {
            Either<Error, T> entityOrError = ReadOnlyRepository<T>::mappingFunction(query);
            if (entityOrError.isLeft()) {
                qCritical() << QString::fromStdString(entityOrError.forceLeft().getMessage());
                return entityOrError.forceLeft();
            }
            entities.push_back(entityOrError.forceRight());
        }
        return entities;
    }

    template<class T>
    optional<Error> CRUDRepository<T>::deleteT(const T& entity) {
        return deleteById(entity.getId());
    }

    template<class T>
    optional<Error> CRUDRepository<T>::deleteById(int id) {
        string sql = ReadOnlyRepository<T>::queryBuilder.deleteT()
                .from(CRUDRepository<T>::table)
                .where(Expr("id").equals({"?"}))
                .build();

        QSqlQuery query = ReadOnlyRepository<T>::exec(sql, QVariant::fromValue<int>(id));
        query.next();

        optional<Error> hasError = ReadOnlyRepository<T>::hasError(query);

        if (hasError.has_value()) {
            qCritical() << QString::fromStdString(
                    hasError.value().getMessage());
        }
        return hasError;
    }


}
#endif //CRUD_REPOSITORY_H
