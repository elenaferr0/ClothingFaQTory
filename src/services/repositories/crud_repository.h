#ifndef CRUD_REPOSITORY_H
#define CRUD_REPOSITORY_H

#include "readonly_repository.h"
#include "../../core/errors/error.h"
#include "../../core/containers/linked_list.h"
#include "../../core/errors/either.h"
#include "../../models/size.h"
#include "../../models/material.h"
#include "../../models/fields_getter_visitor.h"
#include <functional>

using std::function;
using Services::ReadOnlyRepository;
using Core::Error;
using Core::Either;
using Models::Size;
using Models::Material;
using Core::Containers::LinkedList;
using Models::FieldsGetterVisitor;

namespace Services {
    template<class T>
    class CRUDRepository : public ReadOnlyRepository<T> {
        public:
            CRUDRepository(const string& table,
                           function<Either<Error, shared_ptr<T>>(const QSqlQuery&)> mappingFunction)
                    : Repository(table), ReadOnlyRepository<T>(table, mappingFunction) {};

            Either<Error, shared_ptr<T>> save(shared_ptr<T> entity);

            Either<Error, LinkedList<shared_ptr<T>>> saveAll(LinkedList<shared_ptr<T>>& entities);

            optional<Error> deleteT(const T& entity);

            Either<Error, shared_ptr<T>> findById(int id) final override;

            Either<Error, LinkedList<shared_ptr<T>>> findAll() final override;

    };

    template<class T>
    Either<Error, shared_ptr<T>> CRUDRepository<T>::save(shared_ptr<T> entity) {
        string sql;
        QSqlQuery query;
        FieldsGetterVisitor fieldsGetterVisitor;
        entity->accept(fieldsGetterVisitor);
        Map<string, QVariant> fields = fieldsGetterVisitor.getFields();
        LinkedList<string> keys = fields.keys();
        LinkedList<QVariant> values = fields.values();

        if (entity->getId() == -1) { // does not exist
            sql = CRUDRepository<T>::queryBuilder
                    .insertInto(CRUDRepository<T>::table, keys).build();

            query = CRUDRepository<T>::exec(sql, values);
            query.next();
            entity->setId(query.lastInsertId().toInt());
        } else {// exists => should update all the fieldNames

            sql = CRUDRepository<T>::queryBuilder.update(CRUDRepository<T>::table)
                    .set(keys)
                    .where(Expr("id").equals({"?"}))
                    .build();
            keys.pushBack("id");
            values.pushBack(entity->getId());

            query = CRUDRepository<T>::exec(sql, values);
            query.next();
        }

        optional<Error> hasError = CRUDRepository::hasError(query);

        if (hasError.has_value()) {
            qCritical() << QString::fromStdString(hasError.value().getCause());
            return Either<Error, shared_ptr<T>>::ofLeft(hasError.value());
        }

        return entity;
    }

    template<class T>
    Either<Error, LinkedList<shared_ptr<T>>> CRUDRepository<T>::saveAll(LinkedList<shared_ptr<T>>& entities) {
        for (auto en = entities.begin(); en != entities.end(); en++) {
            Either<Error, shared_ptr<T>> entityOrError = save(*en);
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
    Either<Error, shared_ptr<T>> CRUDRepository<T>::findById(int id) {
        string mainEntitySql = Repository::queryBuilder.select()
                .from(Repository::table)
                .where(Expr(Repository::table + ".id").equals({"?"}))
                .build();

        QSqlQuery mainEntityQuery = Repository::exec(mainEntitySql, QVariant::fromValue<int>(id));
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
    Either<Error, LinkedList<shared_ptr<T>>> CRUDRepository<T>::findAll() {
        string sql = Repository::queryBuilder.select()
                .from("ONLY " + Repository::table)
                .build();
        QSqlQuery query = Repository::exec(sql);
        LinkedList<shared_ptr<T>> entities;
        while (query.next()) {
            Either<Error, shared_ptr<T>> entityOrError = ReadOnlyRepository<T>::mappingFunction(query);
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
