#ifndef CRUD_REPOSITORY_H
#define CRUD_REPOSITORY_H

#include "readonly_repository.h"
#include "../../core/errors/error.h"
#include "../../core/containers/linked_list.h"
#include "../../core/errors/either.h"
#include "../../models/size.h"
#include "../../models/material.h"
#include "../../models/fields_getter_visitor.h"
#include "../mappers/hat_mapper.h"
#include <functional>
#include <memory>

using std::function;
using Services::ReadOnlyRepository;
using Core::Error;
using Core::Either;
using Models::Size;
using Models::Material;
using Core::Containers::LinkedList;
using Models::FieldsGetterVisitor;
using std::dynamic_pointer_cast;

namespace Services {
    template<class T>
    class CRUDRepository : public ReadOnlyRepository<T> {
    private:
        static const int COLUMN_NAME_POSITION = 0;

        string getTableColumns();

        string tableColumns;

    public:
        CRUDRepository(const string& table, Mapper* mapper);

        Either<Error, shared_ptr<T>> save(shared_ptr<T> entity);

        Either<Error, LinkedList<shared_ptr<T>>> saveAll(LinkedList<shared_ptr<T>>& entities);

        optional<Error> deleteT(const T& entity);

        Either<Error, shared_ptr<T>> findById(int id) final override;

        Either<Error, LinkedList<shared_ptr<T>>> findAll() final override;

        Either<Error, LinkedList<shared_ptr<T>>> findAllWithFilters(const Filters& filters);

    };

    template<class T>
    CRUDRepository<T>::CRUDRepository(const string& table, Mapper* mapper)
            :Repository(table), ReadOnlyRepository<T>(table, mapper) {
        tableColumns = getTableColumns();
    }

    template<class T>
    string CRUDRepository<T>::getTableColumns() {
        string sql = ReadOnlyRepository<T>::queryBuilder.select("column_name")
                .from("information_schema.columns")
                .where(Expr("table_name").equals({"?"}))
                .build();

        QVariant tableName = QString::fromStdString(ReadOnlyRepository<T>::table);
        QSqlQuery query = ReadOnlyRepository<T>::exec(sql, tableName);
        LinkedList<string> informationSchema;
        while (query.next()) {
            QSqlRecord record = query.record();
            informationSchema.pushBack(record.value(COLUMN_NAME_POSITION).toString().toStdString());
        }

        LinkedList<string> entityFields;
        for (auto i = informationSchema.begin(); i != informationSchema.end(); i++) {
            entityFields.pushBack(Services::ReadOnlyRepository<T>::table + "." + (*i));
        }

        return entityFields.join(", ");
    }

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
        } else {// exists => should update all the fields

            sql = CRUDRepository<T>::queryBuilder.update(CRUDRepository<T>::table)
                    .set(keys)
                    .where(Expr("id").equals({"?"}))
                    .build();
            keys.pushBack("id");
            values.pushBack(entity->getId());
            for (auto i = values.begin(); i != values.end(); i++) {
                qInfo() << *i << Qt::endl;
            }
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

        string sql = Repository::queryBuilder.select(
                        tableColumns + ", size.name as size_name, material.name as material_name, size.*, material.*")
                .from("ONLY " + Repository::table)
                .join(QueryBuilder::INNER, "size", Expr({Repository::table + ".size_id"}).equals({"size.id"}))
                .join(QueryBuilder::INNER, "material",
                      Expr({Repository::table + ".material_id"}).equals({"material.id"}))
                .where(Expr(Repository::table + ".id").equals({"?"}))
                .build();

        QSqlQuery query = Repository::exec(sql, QVariant::fromValue<int>(id));
        query.next();
        Model* model = ReadOnlyRepository<T>::mapper->operator()(query);
        Error* error = ReadOnlyRepository<T>::mapper->getAndResetError();

        if (error) {
            qCritical() << QString::fromStdString(error->getCause());
            return *error; // return the error
        }

        return {shared_ptr<T>(dynamic_cast<T*>(model))};
    }

    template<class T>
    Either<Error, LinkedList<shared_ptr<T>>>
    CRUDRepository<T>::findAllWithFilters(const Filters& filters) {
        QString correspondingProductType = QString::fromStdString(Repository::table).at(0).toUpper() +
                                           QString::fromStdString(Repository::table.substr(1));
        if (filters.getProductTypes().getSize() != 0 && !filters.getProductTypes().contains(correspondingProductType)) {
            return LinkedList<shared_ptr<T>>();
        }

        auto tempQueryBuilder = Repository::queryBuilder.select(
                        tableColumns + ", size.name as size_name, material.name as material_name, size.*, material.*")
                .from("ONLY " + Repository::table)
                .join(QueryBuilder::INNER, "size", Expr({Repository::table + ".size_id"}).equals({"size.id"}))
                .join(QueryBuilder::INNER, "material",
                      Expr({Repository::table + ".material_id"}).equals({"material.id"}));

        if (filters.getCode() != "") {
            tempQueryBuilder = tempQueryBuilder.where(Expr("code").ilike("%" + filters.getCode().toStdString() + "%"));
        }

        if (filters.getOrderByField().first != "") {
            tempQueryBuilder = tempQueryBuilder.orderBy(filters.getOrderByField().first.toStdString(),
                                                        filters.getOrderByField().second);
        }

        return ReadOnlyRepository<T>::findEntities(tempQueryBuilder.build());
    }

    template<class T>
    Either<Error, LinkedList<shared_ptr<T>>> CRUDRepository<T>::findAll() {
        string sql = Repository::queryBuilder.select(
                        tableColumns + ", size.name as size_name, material.name as material_name, size.*, material.*")
                .from("ONLY " + Repository::table)
                .join(QueryBuilder::INNER, "size", Expr({Repository::table + ".size_id"}).equals({"size.id"}))
                .join(QueryBuilder::INNER, "material",
                      Expr({Repository::table + ".material_id"}).equals({"material.id"}))
                .build();
        QSqlQuery query = Repository::exec(sql);
        LinkedList<shared_ptr<T>> entities;

        while (query.next()) {
            Model* model = ReadOnlyRepository<T>::mapper->operator()(query);
            Error* error = ReadOnlyRepository<T>::mapper->getAndResetError();
            if (error) {
                qCritical() << QString::fromStdString(error->getCause());
                error->setUserMessage("Error while fetching " + ReadOnlyRepository<T>::table);
                return *error;
            } else {
                T* ptr = dynamic_cast<T*>(model);
                entities.pushBack(shared_ptr<T>(ptr));
            }
        }
        return entities;
    }

    template<class T>
    optional<Error> CRUDRepository<T>::deleteT(const T& entity) {
        return deleteById(entity.getId());
    }


}
#endif //CRUD_REPOSITORY_H
