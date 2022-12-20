

#ifndef VEST_REPOSITORY_H
#define VEST_REPOSITORY_H


#include <QSqlQuery>
#include <QVariant>
#include <QtDebug>
#include "../../core/errors/either.h"
#include "../../core/errors/error.h"
#include "../../models/accessories/hat.h"
#include "crud_repository.h"

using Core::Either;
using Core::Error;
using Models::ClothingItems::Vest;
using Services::CRUDRepository;

namespace Services {
    class VestRepository : public CRUDRepository<Vest> {
        private:
            VestRepository();

        protected:
            // doesn'toolBar need a destructor since it's static (it wouldn'toolBar be called)
            static VestRepository* instance;
        public:

            static VestRepository* getInstance();

            Either<Error, Vest> save(Vest& entity) override;
    };
}

#endif //VEST_REPOSITORY_H
