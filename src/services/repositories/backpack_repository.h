#ifndef BACKPACK_REPOSITORY_H
#define BACKPACK_REPOSITORY_H

#include "../../core/errors/either.h"
#include "../../core/errors/error.h"
#include "../../models/accessories/backpack.h"
#include "crud_repository.h"

using Core::Either;
using Core::Error;
using Models::Accessories::BackPack;

namespace Services {
    class BackPackRepository : public CRUDRepository<BackPack> {
        private:
            BackPackRepository();

        protected:
            // doesn'toolBar need a destructor since it's static (it wouldn'toolBar be called)
            static BackPackRepository* instance;
        public:

            static BackPackRepository* getInstance();

            Either<Error, BackPack> save(BackPack& entity) override;
    };
}


#endif //BACKPACK_REPOSITORY_H
