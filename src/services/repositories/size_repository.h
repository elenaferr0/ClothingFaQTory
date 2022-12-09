#ifndef SIZEREPOSITORY_H
#define SIZEREPOSITORY_H

#include <QSqlQuery>
#include <QVariant>
#include <QtDebug>
#include "../../core/errors/either.h"
#include "../../core/errors/error.h"
#include "../../models/size.h"
#include "repository.h"

using Core::Either;
using Core::Error;
using Models::Size;
using Services::Repository;

namespace Services {
    class SizeRepository : public Repository<Size> {
    public:
	SizeRepository();

        Either <Error, Size> save(Size& entity) override;

        Either <Error, list<Size>> saveAll(list <Size>& entities) override;

        optional <Error> deleteT(const Size& entity) override;

        Either <Error, Size> findById(int id) override;

        Either <Error, list<Size>> findAll() override;
    };
}
#endif // SIZEREPOSITORY_H
