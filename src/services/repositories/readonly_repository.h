#ifndef READONLY_REPOSITORY_H
#define READONLY_REPOSITORY_H

#include <QDebug>

#include <optional>
#include <string>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <functional>

#include "../../core/db/querybuilder.h"
#include "../../core/errors/either.h"
#include "../../core/errors/error.h"
#include "../../core/filters.h"
#include "../../core/containers/linked_list.h"
#include "../entity_mapper.h"
#include "delete_only_repository.h"
#include "repository.h"

using Core::Containers::LinkedList;
using std::optional;
using std::string;
using std::to_string;
using Core::Db::QueryBuilder;
using Core::Either;
using Core::Filters;
using Core::Error;
using std::function;
using Services::EntityMapper;
using Services::Repository;

namespace Services {
    template<class T>
    class ReadOnlyRepository : virtual public Repository {
        protected:
            function<Either<Error, T*>(const QSqlQuery&)> mappingFunction;

        public:

            ReadOnlyRepository(const string& table,
                               function<Either<Error, T*>(const QSqlQuery&)> mappingFunction);

            virtual ~ReadOnlyRepository() = default;

            ReadOnlyRepository(ReadOnlyRepository&) = delete;

            void operator=(const ReadOnlyRepository&) = delete;

            virtual Either<Error, T*> findById(int id);

            virtual Either<Error, LinkedList<T*>> findAll();

            virtual Either<Error, LinkedList<T*>> findAllWithFilters(Filters filters);

            Either<Error, LinkedList<T*>> findEntities(const string& sql) const;
    };

    template<class T>
    Either<Error, LinkedList<T*>> ReadOnlyRepository<T>::findAllWithFilters(Filters filters) {
        QString correspondingProductType = QString::fromStdString(table).at(0).toUpper() +
                                           QString::fromStdString(table.substr(1));
        if (filters.getProductTypes().getSize() != 0 && !filters.getProductTypes().contains(correspondingProductType)) {
            return LinkedList<T*>();
        }

        auto tempQueryBuilder = queryBuilder
                .select("*")
                .from("ONLY " + table);

        if (filters.getCode() != "") {
            tempQueryBuilder = tempQueryBuilder.where(Expr("code").ilike("%" + filters.getCode().toStdString() + "%"));
        }

        if (filters.getOrderByField().first != "") {
            tempQueryBuilder = tempQueryBuilder.orderBy(filters.getOrderByField().first.toStdString(),
                                                        filters.getOrderByField().second);
        }

        return findEntities(tempQueryBuilder.build());
    }

    template<class T>
    Either<Error, LinkedList<T*>> ReadOnlyRepository<T>::findAll() {
        string sql = Repository::queryBuilder.select()
                .from(Repository::table)
                .orderBy("id", QueryBuilder::Order::ASC)
                .build();
        return findEntities(sql);
    }

    template<class T>
    Either<Error, LinkedList<T*>> ReadOnlyRepository<T>::findEntities(const string& sql) const {
        QSqlQuery query = exec(sql);
        LinkedList<T*> entities;
        while (query.next()) {
            Core::Either<Error, T*> errorOrEntity = mappingFunction(query);
            if (errorOrEntity.isLeft()) {
                qCritical() << QString::fromStdString(errorOrEntity.forceLeft().getCause());
                errorOrEntity.forceLeft().setUserMessage("Error while fetching " + table);
                return errorOrEntity.forceLeft();
            }
            entities.pushBack(errorOrEntity.forceRight());
        }
        return entities;
    }

    template<class T>
    Either<Error, T*> ReadOnlyRepository<T>::findById(int id) {
        string sql = Repository::queryBuilder.select()
                .from(Repository::table)
                .where(Expr("id").equals({"?"}))
                .build();
        QSqlQuery query = Repository::exec(sql, QVariant::fromValue<int>(id));
        query.next(); // is needed so the record can be read
        Either<Error, T*> errorOrEntity = mappingFunction(query);

        if (errorOrEntity.isLeft()) {
            errorOrEntity.forceLeft().setUserMessage("Error while fetching " + Repository::table);
            qCritical() << QString::fromStdString(
                    errorOrEntity.forceLeft().getCause());
        }
        return errorOrEntity;
    }


    template<class T>
    ReadOnlyRepository<T>::ReadOnlyRepository(const string& table,
                                              function<Either<Error, T*>(const QSqlQuery&)> mappingFunction):
            Repository(table),
            mappingFunction(mappingFunction) {};


}

#endif // READONLY_REPOSITORY_H
