#include "size_repository.h"
#include "../../core/db/expression.h"
#include <list>
#include <QDebug>

using Core::Db::Expr;
using std::list;
using Models::Size;
using Services::SizeRepository;

SizeRepository::SizeRepository()
        : ReadOnlyRepository("size") {};


Either<Error, Size> SizeRepository::findById(int id) {
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
    return errorOrSize;
}

Either<Error, list<Size>> SizeRepository::findAll() {
    string sql = queryBuilder.select()
            .from(table)
            .build();
    QSqlQuery query = exec(sql);
    list<Size> sizes;
    while (query.next()) {
        Either<Error, Size> sizeOrError = entityMapper.size(query);
        if (sizeOrError.isLeft()) {
            qCritical() << QString::fromStdString(sizeOrError.left().value().getMessage());
            return sizeOrError.left().value();
        }
        sizes.push_back(sizeOrError.right().value());
    }
    return sizes;
}
