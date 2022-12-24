

#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <string>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "../../core/errors/error.h"
#include "../../core/db/querybuilder.h"
#include <optional>
#include <QVariantList>

using std::optional;
using std::string;
using Core::Error;
using Core::Db::Expr;
using Core::Db::QueryBuilder;

namespace Services {
    class Repository {
        public:
            Repository(const string& table);

            virtual ~Repository() = default;

        protected:
            string table;
            static QueryBuilder queryBuilder;

            static QSqlQuery exec(const string&, const QVariantList&);

            static QSqlQuery exec(const string&, const QVariant&);

            static QSqlQuery exec(const string&);

            static string errorTypeToString(const QSqlError::ErrorType& errorType);

            optional<Error> hasError(const QSqlQuery& query);

    };


}

#endif //REPOSITORY_H
