#ifndef SIZEREPOSITORY_H
#define SIZEREPOSITORY_H

#include "src/models/size.h"
#include "src/core/errors/either.h"
#include "src/core/errors/error.h"
#include "src/services/repositories/repository.h"
#include <QSqlQuery>
#include <QVariant>
#include <QtDebug>

using Core::Either;
using Core::Error;
using Models::Size;
using Services::Repository;

namespace Services {

class SizeRepository : public Repository<Size> {
public:
    SizeRepository(const string& tableName);

    Either <Error, Size> save(Size& entity) override;

    Either <Error, list<Size>> saveAll(list <Size>& entities) override;

    void deleteT(const Size& entity) override;

    Either <Error, Size> findById(int id) override;

    Either <Error, list<Size>> findAll() override;
};
}
#endif // SIZEREPOSITORY_H
