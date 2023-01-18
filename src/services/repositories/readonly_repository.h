#ifndef READONLY_REPOSITORY_H
#define READONLY_REPOSITORY_H

#include <QDebug>

#include <optional>
#include <string>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <functional>
#include <memory>

#include "../../core/db/querybuilder.h"
#include "../../core/errors/either.h"
#include "../../core/errors/error.h"
#include "../../core/filters.h"
#include "../../core/containers/linked_list.h"

#include "delete_only_repository.h"
#include "repository.h"
#include "../mappers/mapper.h"

using Core::Containers::LinkedList;
using std::optional;
using std::string;
using std::to_string;
using std::dynamic_pointer_cast;
using Core::Db::QueryBuilder;
using Core::Either;
using Core::Filters;
using Core::Error;
using std::function;
using Services::Repository;
using std::shared_ptr;

namespace Services {
    template<class T>
    class ReadOnlyRepository : virtual public Repository {

    protected:
        Either<Error, LinkedList<shared_ptr<T>>> findEntities(const string& sql);

        Mapper* mapper;

    public:

        ReadOnlyRepository(const string& table, Mapper* mapper);

        virtual ~ReadOnlyRepository();

        ReadOnlyRepository(ReadOnlyRepository&) = delete;

        void operator=(const ReadOnlyRepository&) = delete;

        virtual Either<Error, shared_ptr<T>> findById(int id);

        virtual Either<Error, LinkedList<shared_ptr<T>>> findAll();
    };

    template<class T>
    ReadOnlyRepository<T>::~ReadOnlyRepository() {
        delete mapper;
    }

    template<class T>
    Either<Error, LinkedList<shared_ptr<T>>>

    ReadOnlyRepository<T>::findAll() {
        string sql = Repository::queryBuilder.select()
                .from(Repository::table)
                .orderBy("id", QueryBuilder::Order::ASC)
                .build();
        return findEntities(sql);
    }

    template<class T>
    Either<Error, LinkedList<shared_ptr<T>>>
    ReadOnlyRepository<T>::findEntities(const string& sql) {
        QSqlQuery query = exec(sql);
        LinkedList<shared_ptr<T>> entities;
        while (query.next()) {
            Model* model = mapper->operator()(query);
            Error* error = mapper->getAndResetError();
            if (error) {
                qCritical() << QString::fromStdString(error->getCause());
                error->setUserMessage("Error while fetching " + table);
                return *error;
            } else {
                entities.pushBack(shared_ptr<T>(dynamic_cast<T*>(model)));
            }
        }
        return entities;
    }

    template<class T>
    Either<Error, shared_ptr<T>> ReadOnlyRepository<T>::findById(int id) {
        string sql = Repository::queryBuilder.select()
                .from(Repository::table)
                .where(Expr("id").equals({"?"}))
                .build();
        QSqlQuery query = Repository::exec(sql, QVariant::fromValue<int>(id));
        query.next(); // is needed so the record can be read

        Model* model = mapper->operator()(query);
        Error* error = mapper->getAndResetError();
        if (error) {
            qCritical() << QString::fromStdString(error->getCause());
            error->setUserMessage("Error while fetching " + table);
            return *error;
        }
        return shared_ptr<T>(dynamic_cast<T*>(model));
    }


    template<class T>
    ReadOnlyRepository<T>::ReadOnlyRepository(const string& table, Mapper* mapper)
            :Repository(table),
             mapper(mapper) {};
}

#endif // READONLY_REPOSITORY_H
