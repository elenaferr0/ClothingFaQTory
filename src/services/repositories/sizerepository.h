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
      Either<Error, Size> save(Size entity);
      list<Size> saveAll(list<Size> entities);
      void deleteT(Size entity);
  };
}
#endif // SIZEREPOSITORY_H
