#include "size_repository.h"
#include <list>

using std::shared_ptr;
using std::make_shared;
using Core::Db::Expr;
using std::list;
using Models::Size;
using Services::SizeRepository;

SizeRepository* SizeRepository::instance;

SizeRepository::SizeRepository()
        : ReadOnlyRepository("size", EntityMapper::size) {};

SizeRepository* Services::SizeRepository::getInstance() {
    if (instance == nullptr) {
        instance = new SizeRepository();
    }
    return instance;
}

Either<Error, shared_ptr<Size>> SizeRepository::findByName(const Size::Name& name) {
    return findById(name);
}

Either<Error, shared_ptr<Size>> SizeRepository::findById(int id) {
    if (cachedSizes.hasKey(id)) {
        return cachedSizes.get(id).value();
    }

    Either<Error, shared_ptr<Size>> errorOrSize = ReadOnlyRepository::findById(id);

    cachedSizes.put(id, errorOrSize.forceRight());
    return errorOrSize;
}

Either<Error, list<shared_ptr<Size>>> Services::SizeRepository::findAll() {
    Either<Error, list<shared_ptr<Size>>> sizesOrError = ReadOnlyRepository::findAll();
    if (sizesOrError.isRight()) {
        for (auto s: sizesOrError.forceRight()) {
            cachedSizes.put(s->getId(), s);
        }
    }
    return sizesOrError;
}
