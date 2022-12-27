#ifndef BRACELET_REPOSITORY_H
#define BRACELET_REPOSITORY_H

#include "../../core/errors/either.h"
#include "../../core/errors/error.h"
#include "../../models/accessories/backpack.h"
#include "crud_repository.h"

using Core::Either;
using Core::Error;
using Models::Accessories::Bracelet;

namespace Services {
    class BraceletRepository : public CRUDRepository<Bracelet> {
        private:
            BraceletRepository();

        protected:

            static BraceletRepository* instance;
        public:

            static BraceletRepository* getInstance();
    };
}


#endif //BRACELET_REPOSITORY_H
