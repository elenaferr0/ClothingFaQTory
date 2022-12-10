#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QDebug>
#include <list>
#include <optional>
#include <string>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <functional>

#include "../../core/db/querybuilder.h"
#include "../../core/errors/either.h"
#include "../../core/errors/error.h"
#include "../entity_mapper.h"

using std::list;
using std::optional;
using std::string;
using std::to_string;
using Core::Db::QueryBuilder;
using Core::Either;
using Core::Error;
using std::function;
using Services::EntityMapper;

namespace Services {
    template<class T>
    class ReadOnlyRepository {
    private:
        string errorTypeToString(const QSqlError::ErrorType& errorType);

    protected:
        string table;
        QueryBuilder queryBuilder;
        EntityMapper entityMapper;

        QSqlQuery exec(const string&, const QVariantList&);

        QSqlQuery exec(const string&, const QVariant&);

        QSqlQuery exec(const string&);

        Either<Error, QSqlRecord> hasErrorOrRecord(const QSqlQuery& query);

        optional<Error> hasError(const QSqlQuery& query);

    public:
        Either<Error, T> findById(int id, function<Either<Error, T>(const QSqlQuery&)> mappingFunction);

        Either<Error, list<T>> findAll(function<Either<Error, T>(const QSqlQuery&)> mappingFunction);

        explicit ReadOnlyRepository(const string& table);

        virtual Either<Error, T> findById(int id) = 0;

        virtual Either<Error, list<T>> findAll() = 0;

        virtual ~ReadOnlyRepository();
    };

    template<class T>
    Either<Error, T>
    ReadOnlyRepository<T>::findById(int id, function<Either<Error, T>(const QSqlQuery&)> mappingFunction) {
        string mainEntitySql = queryBuilder.select()
                .from(table)
                .where(Expr("h.id").equals({"?"}))
                .build();

        string sizeSql = queryBuilder.select("s.*")
                .from(table)
                .join(QueryBuilder::Join::INNER, "size", Expr("s.id").equals({"h.size_id"}))
                .where(Expr("h.id").equals({"?"}))
                .build();

        string materialSql = queryBuilder.select("m.*")
                .from(table)
                .join(QueryBuilder::Join::INNER, "material", Expr("m.id").equals({"h.material_id"}))
                .where(Expr("h.id").equals({"?"}))
                .build();

        // get the entity
        QSqlQuery mainEntityQuery = exec(mainEntitySql, QVariant::fromValue<int>(id));
        mainEntityQuery.next();
        Either<Error, T> errorOrEntity = mappingFunction(mainEntityQuery);

        if (errorOrEntity.isLeft()) {
            qCritical() << QString::fromStdString(
                    errorOrEntity.forceLeft().getMessage());
            QSqlDatabase::database().rollback();
            return errorOrEntity; // return the error
        }

        // get the size
        QSqlQuery sizeQuery = exec(sizeSql, QVariant::fromValue<int>(id));
        sizeQuery.next();
        Either<Error, Size> errorOrSize = entityMapper.size(sizeQuery);

        if (errorOrSize.isLeft()) {
            qCritical() << QString::fromStdString(
                    errorOrSize.forceLeft().getMessage());
            QSqlDatabase::database().rollback();
            return errorOrSize.forceLeft(); // return the error
        }

        errorOrEntity.forceRight().setSize(errorOrSize.forceRight());

        // get the material
        QSqlQuery materialQuery = exec(materialSql, QVariant::fromValue<int>(id));
        materialQuery.next();
        Either<Error, Material> errorOrMaterial = entityMapper.material(materialQuery);

        if (errorOrMaterial.isLeft()) {
            qCritical() << QString::fromStdString(
                    errorOrMaterial.forceLeft().getMessage());
            return errorOrMaterial.forceLeft(); // return the error
        }

        errorOrEntity.forceRight().setMaterial(errorOrMaterial.forceRight());
        return errorOrEntity.forceRight();
    }

    template<class T>
    Either<Error, list<T>> ReadOnlyRepository<T>::findAll(function<Either<Error, T>(const QSqlQuery&)> mappingFunction) {
        string sql = queryBuilder.select()
                .from(table)
                .build();
        QSqlQuery query = exec(sql);
        list<T> entities;
        while (query.next()) {
            Either<Error, T> entityOrError = mappingFunction(query);
            if (entityOrError.isLeft()) {
                qCritical() << QString::fromStdString(entityOrError.forceLeft().getMessage());
                return entityOrError.forceLeft();
            }
            entities.push_back(entityOrError.forceRight());
        }
        return entities;
    }


    template<class T>
    Either<Error, QSqlRecord> ReadOnlyRepository<T>::hasErrorOrRecord(const QSqlQuery& query) {
        // avoids error checking code duplication
        QSqlError error = query.lastError();

        if (!query.isValid() || error.type() != QSqlError::NoError) { // error occurred
            return Error({errorTypeToString(error.type()), error.text().toStdString()});
        }

        return query.record();
    }

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


    template<class T>
    string ReadOnlyRepository<T>::errorTypeToString(const QSqlError::ErrorType& errorType) {
        switch (errorType) {
            case QSqlError::ConnectionError:
                return "Connection Error";
            case QSqlError::StatementError:
                return "Statement Error";
            case QSqlError::TransactionError:
                return "Transaction Error";
            case QSqlError::UnknownError:
                return "Unknown Error";
            default:
                return "";
        }
    }

    template<class T>
    optional<Error> ReadOnlyRepository<T>::hasError(const QSqlQuery& query) {
        QSqlError error = query.lastError();
        if (error.type() != QSqlError::NoError) {
            return optional<Error>({errorTypeToString(error.type()),
                                    error.text().toStdString()});
        }
        return nullopt;
    }

}

#endif // REPOSITORY_H
