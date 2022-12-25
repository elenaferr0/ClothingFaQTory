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
        private:
            SizeRepository();

        protected:
            static SizeRepository* instance;
            Map<int, Size*> cachedSizes; // not static since there's only an instance

        public:

            Either<Error, Size*> findById(int id) override;

            Either<Error, Size*> findByName(const Size::Name&);

            Either<Error, list<Size*>> findAll() override;

            static SizeRepository* getInstance();

            ~SizeRepository();

    };
}
#endif // SIZEREPOSITORY_H
