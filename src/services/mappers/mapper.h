

#ifndef MAPPER_H
#define MAPPER_H

#include <QSqlQuery>
#include <memory>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>
#include "../../core/errors/error.h"
#include "../../core/errors/either.h"
#include "../../models/model.h"

using std::make_shared;
using Core::Error;
using Core::Either;
using std::shared_ptr;
using Models::Model;

namespace Services {
    class Mapper {
        protected:
            Error* lastError;

            static string toString(const QSqlError::ErrorType& errorType);

            void checkQuery(const QSqlQuery& query);

        public:
            Mapper();

            virtual Model* operator()(const QSqlQuery&) = 0;

            virtual ~Mapper();

            Error* getAndResetError();
    };

}

#endif //MAPPER_H
