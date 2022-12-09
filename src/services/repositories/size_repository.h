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
    public:
        SizeRepository();

        Either<Error, Size> findById(int id) override;

        Either<Error, list<Size>> findAll() override;

    };
}
#endif // SIZEREPOSITORY_H
