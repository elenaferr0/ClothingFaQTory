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
        : ReadOnlyRepository("size") {};

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
                errorOrSize.forceLeft().getMessage());
    }
    sizes[id] = errorOrSize.forceRight();
    return errorOrSize;
}

Either<Error, list<Size>> Services::SizeRepository::findAll() {
    string sql = queryBuilder.select()
            .from(table)
            .build();
    QSqlQuery query = exec(sql);
    list<Size> dbSizes;
    while (query.next()) {
        Either<Error, Size> errorOrSize = entityMapper.size(query);
        if (errorOrSize.isLeft()) {
            qCritical() << QString::fromStdString(
                    errorOrSize.forceLeft().getMessage());
            return errorOrSize.forceLeft();
        }
        Size& size = errorOrSize.forceRight();
        dbSizes.push_back(size);
        sizes[size.getId()] = errorOrSize.forceRight();
    }
    return dbSizes;
}
