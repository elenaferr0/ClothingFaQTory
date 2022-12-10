#ifndef SIZEREPOSITORY_H
#define SIZEREPOSITORY_H

#include <QSqlQuery>
#include <QVariant>
#include <QtDebug>
#include "../../core/errors/either.h"
#include "../../core/errors/error.h"
#include "../../models/size.h"
#include "readonly_repository.h"

using Core::Either;
using Core::Error;
using Models::Size;

namespace Services {
    class SizeRepository : public ReadOnlyRepository<Size> {
    protected:
        SizeRepository();

        static SizeRepository* instance; // no need for destructor since it's static
        Map<int, Size> sizes; // not static since there's only an instance

    public:
        SizeRepository(SizeRepository&) = delete;

        void operator=(const SizeRepository&) = delete;

        Either<Error, Size> findById(int id) override;

        Either<Error, Size> findByName(const Size::Name&);

        Either<Error, list<Size>> findAll() override;

        static SizeRepository* getInstance();

    };
}
#endif // SIZEREPOSITORY_H
