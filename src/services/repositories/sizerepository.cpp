#include "sizerepository.h"
#include <list>
#include <QDebug>

using std::list;
using Models::Size;
using Services::SizeRepository;

SizeRepository::SizeRepository(const string& table)
        : Repository(table) {};


Either <Error, Size> SizeRepository::findById(int id) {
    string sql = queryBuilder.select()
            .from(table)
            .where(Expr("id").equals({"?"}))
	    .build();
    QSqlQuery query = exec(sql, QVariant::fromValue<int>(id));
    query.next(); // is needed so the record can be read
    return entityMapper.size(query);
}

Either <Error, Size> SizeRepository::save(Size& entity) {
    // check if that size already exist
    QSqlDatabase::database().transaction();

    QSqlQuery query;
    string sql;
    list <string> fields = {"name", "extra_percentage_of_material"};

    if (entity.getId() == -1) { // does not exist => create a new Size
	Size size = Size();
	size.setName(entity.getName());
        size.setExtraPercentageOfMaterial(entity.getExtraPercentageOfMaterial());

        string sql = queryBuilder.insertInto("size", fields).build();
        query = exec(sql);
	query.next();
	Either <Error, Size> result = entityMapper.size(query);
	if (result.isLeft()) {
	    QSqlDatabase::database().rollback();
	} else {
	    QSqlDatabase::database().commit();
	}

	return result;
    }

    // exists => should update all the fields
    sql = queryBuilder.update("size")
	    .set(fields)
	    .where(Expr("id").equals({"?"}))
	    .build();

    QVariantList params;
    params << QString::fromStdString(entity.getName())
	   << entity.getExtraPercentageOfMaterial()
	   << entity.getId();

    query = exec(sql, params);
    //    query.next();
    //    qInfo() << query.isValid() << " " << query.isActive();
    //    optional<Error> hasError = entityMapper.hasError(query);
	qInfo() << query.lastError();
    //    qInfo() << query.lastError().type();

    //    if (hasError.has_value()) {
    //	QSqlDatabase::database().rollback();
    //	return Either<Error, Size>::ofLeft(hasError.value());
    //    }

    QSqlDatabase::database().commit();
    return Either<Error, Size>::ofRight(entity);
}

Either <Error, list<Size>> SizeRepository::saveAll(list <Size>& entities) {
    // entities returned by save are inserted in a new list
    // in order to get also the id of the newly created ones
    list <Size> sizes;
    for (auto it = entities.begin(); it != entities.end(); it++) {
        Either <Error, Size> sizeOrError = save(*it);
        if (sizeOrError.isLeft()) {
            return Either < Error, list < Size >> ::ofLeft(sizeOrError.left().value());
        } else {
            sizes.push_back(sizeOrError.right().value());
        }
    }
    return Either < Error, list < Size >> ::ofRight(sizes);
}

void SizeRepository::deleteT(const Size& entity) {
    string sql = queryBuilder.deleteT()
            .from(table)
            .where(Expr("id").equals({":id"}))
            .build();
    QVariantList params;
    params << QVariant::fromValue<int>(entity.getId());
    exec(sql, params);
}

Either <Error, list<Size>> SizeRepository::findAll() {
    string sql = queryBuilder.select()
            .from(table)
            .build();
    QSqlQuery query = exec(sql);
    list <Size> sizes;
    while (query.next()) {
        Either <Error, Size> sizeOrError = entityMapper.size(query);
        if (sizeOrError.isLeft()) {
            qWarning() << QString::fromStdString(
                    sizeOrError.left().value().getMessage());
        }
        sizes.push_back(sizeOrError.right().value());
    }
    return sizes;
}
