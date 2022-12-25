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
        private:
            HatRepository();
        protected:
            static HatRepository* instance;
        public:
            static HatRepository* getInstance();

            Either<Error, Hat*> save(Hat* entity) override;
    };
}
#endif // HATREPOSITORY_H
