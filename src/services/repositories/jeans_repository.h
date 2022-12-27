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

            static JeansRepository* instance;
        public:

            static JeansRepository* getInstance();

    };
}


#endif //JEANS_REPOSITORY_H
