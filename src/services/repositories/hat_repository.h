#ifndef HATREPOSITORY_H
#define HATREPOSITORY_H

#include <QSqlQuery>
#include <QVariant>
#include <QtDebug>
#include "../../core/errors/either.h"
#include "../../core/errors/error.h"
#include "../../models/accessories/hat.h"
#include "repository.h"

using Core::Either;
using Core::Error;
using Models::Accessories::Hat;
using Services::Repository;

namespace Services {
    class HatRepository : public Repository<Hat> {
    public:
        HatRepository();

        Either<Error, Hat> save(Hat& entity) override;

        Either<Error, list<Hat>> saveAll(list<Hat>& entities) override;

        optional<Error> deleteT(const Hat& entity) override;

        Either<Error, Hat> findById(int id) override;

        Either<Error, list<Hat>> findAll() override;
    };
}
#endif // HATREPOSITORY_H
