#ifndef HATREPOSITORY_H
#define HATREPOSITORY_H

#include <QSqlQuery>
#include <QVariant>
#include <QtDebug>
#include "../../core/errors/either.h"
#include "../../core/errors/error.h"
#include "../../models/accessories/hat.h"
#include "crud_repository.h"

using Core::Either;
using Core::Error;
using Models::Accessories::Hat;
using Services::CRUDRepository;

namespace Services {
    class HatRepository : public CRUDRepository<Hat> {
    protected:
        HatRepository();

        static HatRepository* instance;
    public:

        HatRepository(HatRepository&) = delete;

        void operator=(const HatRepository&) = delete;

        static HatRepository* getInstance();

        Either<Error, Hat> save(Hat& entity) override;

        Either<Error, list<Hat>> saveAll(list<Hat>& entities) override;

//        optional<Error> deleteT(const Hat& entity) override;

//        optional<Error> deleteById(int id) override;

        Either<Error, Hat> findById(int id) override;

        Either<Error, list<Hat>> findAll() override;
    };
}
#endif // HATREPOSITORY_H
