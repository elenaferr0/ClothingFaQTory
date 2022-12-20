#ifndef JEANS_REPOSITORY_H
#define JEANS_REPOSITORY_H


#include "../../core/errors/either.h"
#include "../../core/errors/error.h"
#include "crud_repository.h"

using Core::Either;
using Core::Error;

namespace Services {
    class JeansRepository : public CRUDRepository<Jeans> {
        private:
            JeansRepository();

        protected:
            // doesn'toolBar need a destructor since it's static (it wouldn'toolBar be called)
            static JeansRepository* instance;
        public:

            static JeansRepository* getInstance();

            Either<Error, Jeans> save(Jeans& entity) override;
    };
}


#endif //JEANS_REPOSITORY_H
