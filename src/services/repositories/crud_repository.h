#ifndef CRUD_REPOSITORY_H
#define CRUD_REPOSITORY_H

#include "readonly_repository.h"
#include "../../core/errors/error.h"
#include "../../core/containers/linked_list.h"
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
using Core::Containers::LinkedList;

namespace Services {
    template<class T>
    class CRUDRepository : public ReadOnlyRepository<T> {
        protected:
            Either<Error, T*> save(const LinkedList<string>&, QVariantList&, T* entity);

        public:
            CRUDRepository(const string& table,
                           function<Either<Error, T*>(const QSqlQuery&)> mappingFunction)
                    : ReadOnlyRepository<T>(table, mappingFunction) {};

            virtual Either<Error, T*> save(T* entity) = 0;

            Either<Error, LinkedList<T*>> saveAll(LinkedList<T*>& entities);

            optional<Error> deleteT(const T& entity);

            Either<Error, T*> findById(int id) override;

            Either<Error, LinkedList<T*>> findAll() override;

    };

    template<class T>
    Either<Error, T*> CRUDRepository<T>::save(const LinkedList<string>& fields, QVariantList& params, T* entity) {
        string sql;
        QSqlQuery query;

        if (entity->getId() == -1) { // does not exist
            sql = CRUDRepository<T>::queryBuilder
                    .insertInto(CRUDRepository<T>::table, fields).build();

            query = CRUDRepository<T>::exec(sql, params);
            query.next();
            entity->setId(query.lastInsertId().toInt());
        } else {
            // exists => should update all the fields
            sql = CRUDRepository<T>::queryBuilder.update(CRUDRepository<T>::table)
                    .set(fields)
                    .where(Expr("id").equals({"?"}))
                    .build();

            params << entity->getId();
            query = CRUDRepository<T>::exec(sql, params);
            query.next();
        }

        optional<Error> hasError = CRUDRepository::hasError(query);

        if (hasError.has_value()) {
            qCritical() << QString::fromStdString(hasError.value().getCause());
            return Either<Error, T*>::ofLeft(hasError.value());
        }

        return entity;
    }

    template<class T>
    Either<Error, LinkedList<T*>> CRUDRepository<T>::saveAll(LinkedList<T*>& entities) {
        for (auto en = entities.begin(); en != entities.end(); en++) {
            Either<Error, T*> entityOrError = save(*en);
            if (entityOrError.isLeft()) {
                entityOrError.forceLeft().setUserMessage("Error while fetching " + Repository::table);
                qCritical() << QString::fromStdString(entityOrError.forceLeft().getCause());
                return entityOrError.forceLeft();
            }

            *en = entityOrError.forceRight();
        }
        return entities;
    }

    template<class T>
    Either<Error, T*> CRUDRepository<T>::findById(int id) {
        string mainEntitySql = Repository::queryBuilder.select()
                .from(Repository::table)
                .where(Expr("h.id").equals({"?"}))
                .build();

        QSqlQuery mainEntityQuery = Repository::exec(mainEntitySql, QVariant::fromValue<int>(id));
        mainEntityQuery.next();
        Either<Error, T*> errorOrEntity = ReadOnlyRepository<T>::mappingFunction(mainEntityQuery);
        if (errorOrEntity.isLeft()) {
            qCritical() << QString::fromStdString(
                    errorOrEntity.forceLeft().getCause());
            return errorOrEntity; // return the error
        }

        return errorOrEntity.forceRight();
    }

    template<class T>
    Either<Error, LinkedList<T*>> CRUDRepository<T>::findAll() {
        string sql = Repository::queryBuilder.select()
                .from(Repository::table)
                .build();
        QSqlQuery query = Repository::exec(sql);
        LinkedList<T*> entities;
        while (query.next()) {
            Either<Error, T*> entityOrError = ReadOnlyRepository<T>::mappingFunction(query);
            if (entityOrError.isLeft()) {
                qCritical() << QString::fromStdString(entityOrError.forceLeft().getCause());
                return entityOrError.forceLeft();
            }
            entities.pushBack(entityOrError.forceRight());
        }
        return entities;
    }

    template<class T>
    optional<Error> CRUDRepository<T>::deleteT(const T& entity) {
        return deleteById(entity.getId());
    }


}
#endif //CRUD_REPOSITORY_H
