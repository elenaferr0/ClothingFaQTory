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
        // doesn't need a destructor since it's static (it wouldn't be called)
        static BraceletRepository* instance;
    public:

        static BraceletRepository* getInstance();

        Either<Error, Bracelet> save(Bracelet& entity) override;
    };
}


#endif //BRACELET_REPOSITORY_H