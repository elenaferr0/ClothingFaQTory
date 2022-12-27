#include "size_repository.h"


using Core::Db::Expr;

using Models::Size;
using Services::SizeRepository;

SizeRepository* SizeRepository::instance;

SizeRepository::SizeRepository()
        : Repository("size"), ReadOnlyRepository("size", EntityMapper::size) {};

SizeRepository* Services::SizeRepository::getInstance() {
    if (instance == nullptr) {
        instance = new SizeRepository();
    }
    return instance;
}

Either<Error, Size*> SizeRepository::findByName(const Size::Name& name) {
    return findById(name);
}

Either<Error, Size*> SizeRepository::findById(int id) {
    if (cachedSizes.hasKey(id)) {
        return cachedSizes.get(id).value();
    }

    Either<Error, Size*> errorOrSize = ReadOnlyRepository::findById(id);

    cachedSizes.put(id, errorOrSize.forceRight());
    return errorOrSize;
}

Either<Error, LinkedList<Size*>> Services::SizeRepository::findAll() {
    Either<Error, LinkedList<Size*>> sizesOrError = ReadOnlyRepository::findAll();
    if (sizesOrError.isRight()) {
        for (auto s: sizesOrError.forceRight()) {
            cachedSizes.put(s->getId(), s);
        }
    }
    return sizesOrError;
}

Services::SizeRepository::~SizeRepository() {
    for (auto it = cachedSizes.cbegin(); it != cachedSizes.cend(); it++) {
        delete (*it).second;
    }
}
