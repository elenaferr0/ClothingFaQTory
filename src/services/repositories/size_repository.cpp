#include "size_repository.h"
#include "../../core/db/expression.h"
#include <list>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>

using Core::Db::Expr;
using std::list;
using Models::Size;
using Services::SizeRepository;

SizeRepository* SizeRepository::instance;

SizeRepository::SizeRepository()
        : ReadOnlyRepository("size", entityMapper.size) {};

SizeRepository* Services::SizeRepository::getInstance() {
    if (instance == nullptr) {
        instance = new SizeRepository();
    }
    return instance;
}


Either<Error, Size> Services::SizeRepository::findByName(const Size::Name& name) {
    return findById(name);
}

Either<Error, Size> Services::SizeRepository::findById(int id) {
    if (cachedSizes.hasKey(id)) {
        return cachedSizes.get(id).value();
    }

    Either<Error, Size> errorOrSize = ReadOnlyRepository::findById(id);

    cachedSizes[id] = errorOrSize.forceRight();
    return errorOrSize;
}

Either<Error, list<Size>> Services::SizeRepository::findAll() {
    Either<Error, list<Size>> sizeOrError = ReadOnlyRepository::findAll();
    if(sizeOrError.isRight()){
        for (auto s : sizeOrError.forceRight()) {
            cachedSizes[s.getId()] = s;
        }
    }
    return sizeOrError;
}
