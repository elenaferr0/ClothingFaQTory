#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QDebug>
#include <list>
#include <optional>
#include <string>
#include "../entity_mapper.h"
#include "../../core/db/querybuilder.h"

using std::list;
using std::optional;
using std::string;
using std::to_string;
using Core::Db::QueryBuilder;
using Services::EntityMapper;
using Core::Either;
using Core::Error;

namespace Services {
    template<class T>
    class ReadOnlyRepository {
    protected:
        string table;
        QueryBuilder queryBuilder;
        EntityMapper entityMapper;

        QSqlQuery exec(const string&, const QVariantList&);

        QSqlQuery exec(const string&, const QVariant&);

        QSqlQuery exec(const string&);

    public:
        explicit ReadOnlyRepository(const string& table);

        virtual Either<Error, T> findById(int id) = 0;

        virtual Either<Error, list<T>> findAll() = 0;

        virtual ~ReadOnlyRepository();
    };

    template<class T>
    ReadOnlyRepository<T>::~ReadOnlyRepository() {}

    template<class T>
    QSqlQuery ReadOnlyRepository<T>::exec(const string& sql, const QVariantList& params) {
        QSqlQuery query;
        query.prepare(QString::fromStdString(sql));
        for (int i = 0; i < params.count(); i++) {
            query.bindValue(i, params.at(i));
        }
        query.exec();
        return query;
    }

    template<class T>
    QSqlQuery ReadOnlyRepository<T>::exec(const string& sql, const QVariant& param) {
        QSqlQuery query;
        query.prepare(QString::fromStdString(sql));
        query.addBindValue(param);
        query.exec();
        qInfo() << query.lastQuery();
        return query;
    }

    template<class T>
    QSqlQuery ReadOnlyRepository<T>::exec(const string& sql) {
        QSqlQuery query;
        query.exec(QString::fromStdString(sql));
        qInfo() << query.lastQuery();
        return query;
    }

    template<class T>
    ReadOnlyRepository<T>::ReadOnlyRepository(const string& table): table(table) {};
}

#endif // REPOSITORY_H
