#ifndef OVERALLS_REPOSITORY_H
#define OVERALLS_REPOSITORY_H

#include "../../core/errors/either.h"
#include "../../core/errors/error.h"
#include "crud_repository.h"
#include "../../models/clothing_items/overalls.h"

using Core::Either;
using Core::Error;
using Core::Either;
using Core::Error;
using Services::CRUDRepository;
using Models::ClothingItems::Overalls;

namespace Services {
    class OverallsRepository : public CRUDRepository<Overalls> {
        private:
            OverallsRepository();

        protected:

            static OverallsRepository* instance;
        public:

            static OverallsRepository* getInstance();

            Either<Error, Overalls*> save(Overalls* entity) override;
    };
};

#endif //OVERALLS_REPOSITORY_H
