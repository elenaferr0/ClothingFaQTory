#ifndef CRUD_REPOSITORY_H
#define CRUD_REPOSITORY_H

#include "readonly_repository.h"

namespace Services {
    template<class T>
    class CRUDRepository : public ReadOnlyRepository<T> {
    public:
        explicit CRUDRepository(const string& table) : ReadOnlyRepository<T>(table) {};

        virtual Either<Error, T> save(T& entity) = 0;

        virtual Either<Error, list<T>> saveAll(list<T>& entities) = 0;

        virtual optional<Error> deleteT(const T& entity) = 0;

        virtual optional<Error> deleteById(int id) = 0;
    };
}
#endif //CRUD_REPOSITORY_H
