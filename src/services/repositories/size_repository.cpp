#include "size_repository.h"
#include "../../core/db/expression.h"
#include <list>
#include <QDebug>

using Core::Db::Expr;
using std::list;
using Models::Size;
using Services::SizeRepository;

SizeRepository* SizeRepository::instance;

SizeRepository::SizeRepository()
        : ReadOnlyRepository("size") {};


Either<Error, Size> SizeRepository::findById(int id) {
    if (sizes.hasKey(id)) {
        return sizes.get(id).value();
    }

    string sql = queryBuilder.select()
            .from(table)
            .where(Expr("id").equals({"?"}))
            .build();
    QSqlQuery query = exec(sql, QVariant::fromValue<int>(id));
    query.next(); // is needed so the record can be read
    Either<Error, Size> errorOrSize = entityMapper.size(query);

    if (errorOrSize.isLeft()) {
        qCritical() << QString::fromStdString(
                errorOrSize.left().value().getMessage());
    }
    sizes[id] = errorOrSize.right().value();
    return errorOrSize;
}

SizeRepository* Services::SizeRepository::getInstance() {
    if (instance == nullptr) {
        instance = new SizeRepository();
    }
    return instance;
}

Either<Error, list<Size>> SizeRepository::findAll() {
    string sql = queryBuilder.select()
            .from(table)
            .build();
    QSqlQuery query = exec(sql);
    list<Size> dbSizes;
    while (query.next()) {
        Either<Error, Size> errorOrSize = entityMapper.size(query);
        if (errorOrSize.isLeft()) {
            qCritical() << QString::fromStdString(
                    errorOrSize.left().value().getMessage());
            return errorOrSize.left().value();
        }
        Size size = errorOrSize.right().value();
        dbSizes.push_back(size);
        sizes[size.getId()] = errorOrSize.right().value();
    }
    return dbSizes;
}

Either<Error, Size> Services::SizeRepository::findByName(const Size::Name& name) {
    return findById(name);
}
