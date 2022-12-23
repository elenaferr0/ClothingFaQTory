#ifndef CRUD_REPOSITORY_H
#define CRUD_REPOSITORY_H

#include "readonly_repository.h"
#include "../../core/errors/error.h"
#include "../../core/errors/either.h"
#include "../../models/size.h"
#include "../../models/material.h"
#include <functional>
#include <memory>

using std::shared_ptr;
using std::function;
using Services::ReadOnlyRepository;
using Core::Error;
using Core::Either;
using Models::Size;
using Models::Material;

namespace Services {
    template<class T>
    class CRUDRepository : public ReadOnlyRepository<T> {
        protected:
            Either<Error, T> save(const list<string>&, QVariantList&, T& entity);

        public:
            CRUDRepository(const string& table,
                           function<Either<Error, shared_ptr<T>>(const QSqlQuery&)> mappingFunction)
                    : ReadOnlyRepository<T>(table, mappingFunction) {};

            virtual Either<Error, T> save(T& entity) = 0;

            Either<Error, list<T>> saveAll(list<T>& entities);

            optional<Error> deleteT(const T& entity);

            optional<Error> deleteById(int id);

            Either<Error, shared_ptr<T>> findById(int id) override;

            Either<Error, list<shared_ptr<T>>> findAll() override;

    };

    template<class T>
    Either<Error, T> CRUDRepository<T>::save(const list<string>& fields, QVariantList& params, T& entity) {
        string sql;
        QSqlQuery query;

        if (entity.getId() == -1) { // does not exist
            sql = CRUDRepository<T>::queryBuilder
                    .insertInto(CRUDRepository<T>::table, fields).build();

            query = CRUDRepository<T>::exec(sql, params);
            query.next();
            entity.setId(query.lastInsertId().toInt());
        } else {
            // exists => should update all the fields
            sql = CRUDRepository<T>::queryBuilder.update(CRUDRepository<T>::table)
                    .set(fields)
                    .where(Expr("id").equals({"?"}))
                    .build();

            params << entity.getId();
            query = CRUDRepository<T>::exec(sql, params);
            query.next();
        }

        optional<Error> hasError = CRUDRepository::hasError(query);

        if (hasError.has_value()) {
            qCritical() << QString::fromStdString(hasError.value().getCause());
            return Either<Error, T>::ofLeft(hasError.value());
        }

        return entity;
    }

    template<class T>
    Either<Error, list<T>> CRUDRepository<T>::saveAll(list<T>& entities) {
        for (auto en = entities.begin(); en != entities.end(); en++) {
            Either<Error, T> entityOrError = save(*en);
            if (entityOrError.isLeft()) {
                entityOrError.forceLeft().setUserMessage("Error while fetching " + ReadOnlyRepository<T>::table);
                qCritical() << QString::fromStdString(entityOrError.forceLeft().getCause());
                return entityOrError.forceLeft();
            }

            *en = entityOrError.forceRight();
        }
        return entities;
    }

    template<class T>
    Either<Error, shared_ptr<T>> CRUDRepository<T>::findById(int id) {
        string mainEntitySql = ReadOnlyRepository<T>::queryBuilder.select()
                .from(ReadOnlyRepository<T>::table)
                .where(Expr("h.id").equals({"?"}))
                .build();

        QSqlQuery mainEntityQuery = ReadOnlyRepository<T>::exec(mainEntitySql, QVariant::fromValue<int>(id));
        mainEntityQuery.next();
        Either<Error, shared_ptr<T>> errorOrEntity = ReadOnlyRepository<T>::mappingFunction(mainEntityQuery);
        if (errorOrEntity.isLeft()) {
            qCritical() << QString::fromStdString(
                    errorOrEntity.forceLeft().getCause());
            return errorOrEntity; // return the error
        }

        return errorOrEntity.forceRight();
    }

    template<class T>
    Either<Error, list<shared_ptr<T>>> CRUDRepository<T>::findAll() {
        string sql = ReadOnlyRepository<T>::queryBuilder.select()
                .from(ReadOnlyRepository<T>::table)
                .build();
        QSqlQuery query = ReadOnlyRepository<T>::exec(sql);
        list<shared_ptr<T>> entities;
        while (query.next()) {
            Either<Error, shared_ptr<T>> entityOrError = ReadOnlyRepository<T>::mappingFunction(query);
            if (entityOrError.isLeft()) {
                qCritical() << QString::fromStdString(entityOrError.forceLeft().getCause());
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
                    hasError.value().getCause());
        }
        return hasError;
    }


}
#endif //CRUD_REPOSITORY_H
