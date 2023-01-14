#include "repository.h"

using Services::Repository;

QueryBuilder Services::Repository::queryBuilder;

Repository::~Repository() = default;

QSqlQuery Repository::exec(const string& sql, const LinkedList<QVariant>& params) {
    QSqlQuery query;
    query.prepare(QString::fromStdString(sql));
    int i = 0;
    for (auto p = params.begin(); p != params.end(); p++, i++) {
        query.bindValue(i, *p);
    }
    query.exec();
    qInfo() << query.lastQuery();
    return query;
}

QSqlQuery Repository::exec(const string& sql, const QVariant& param) {
    QSqlQuery query;
    query.prepare(QString::fromStdString(sql));
    query.addBindValue(param);
    query.exec();
    qInfo() << query.lastQuery();
    return query;
}

QSqlQuery Repository::exec(const string& sql) {
    QSqlQuery query;
    query.exec(QString::fromStdString(sql));
    qInfo() << query.lastQuery();
    return query;
}

string Repository::errorTypeToString(const QSqlError::ErrorType& errorType) {
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

optional<Error> Repository::hasError(const QSqlQuery& query) {
    QSqlError error = query.lastError();
    if (error.type() != QSqlError::NoError) {
        return optional<Error>({errorTypeToString(error.type()),
                                error.text().toStdString(),
                                "Error while fetching " + table});
    }
    return nullopt;
}

Repository::Repository(const string& table) : table(table) {}
