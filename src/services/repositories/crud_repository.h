#ifndef CRUD_REPOSITORY_H
#define CRUD_REPOSITORY_H

#include "readonly_repository.h"
#include "../../core/errors/error.h"
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

namespace Services {
    template<class T>
    class CRUDRepository : public ReadOnlyRepository<T> {
    public:
        explicit CRUDRepository(const string& table) : ReadOnlyRepository<T>(table) {};

        virtual Either<Error, T> save(T& entity) = 0;

        virtual Either<Error, list<T>> saveAll(list<T>& entities) = 0;

        optional<Error> deleteT(const T& entity);

        optional<Error> deleteById(int id);

    };

    template<class T>
    optional<Error> CRUDRepository<T>::deleteT(const T& entity) {
        return deleteById(entity.getId());
    }

    template<class T>
    optional<Error> CRUDRepository<T>::deleteById(int id) {
        string sql = ReadOnlyRepository<T>::queryBuilder.deleteT()
                .from(CRUDRepository<T>::table)
                .where(Expr("id").equals({"?"}))
                .build();

        QSqlQuery query = ReadOnlyRepository<T>::exec(sql, QVariant::fromValue<int>(id));
        query.next();

        optional<Error> hasError = ReadOnlyRepository<T>::hasError(query);

        if (hasError.has_value()) {
            qCritical() << QString::fromStdString(
                    hasError.value().getMessage());
        }
        return hasError;
    }


}
#endif //CRUD_REPOSITORY_H
