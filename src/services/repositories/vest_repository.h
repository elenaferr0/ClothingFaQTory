

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

            static VestRepository* instance;
        public:

            static VestRepository* getInstance();
    };
}

#endif //VEST_REPOSITORY_H
