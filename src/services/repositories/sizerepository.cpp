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
//	  .bindParameter(":id", to_string(id))
            .build();
    QSqlQuery query = exec(sql, QVariant::fromValue<int>(id));
    return entityMapper.size(query);
}

Either <Error, Size> SizeRepository::save(Size& entity) {
    // check if that size already exist
    QSqlDatabase::database().transaction();

    string sql = queryBuilder.select("id")
            .from(table)
            .where(Expr("id").equals({":id"}))
            .build();
    QSqlQuery query = exec(sql, QVariant::fromValue<int>(entity.getId()));

    Either <Error, Size> result = entityMapper.size(query);

    if (result.isLeft()) {
        QSqlDatabase::database().rollback();
        return result;
    }

    Size size = result.right().value();
    size.setName(entity.getName());
    size.setExtraPercentageOfMaterial(entity.getExtraPercentageOfMaterial());
    Map <string, string> fields;
    fields["name"] = size.getName();
    fields["extra_percentage_of_material"] = size.getExtraPercentageOfMaterial();

    if (size.getId() == -1) { // does not exist => create a new Size
        sql = queryBuilder.insertInto("size", fields).build();
        query = exec(sql);
    } else { // exists => should update all the fields
        sql = queryBuilder.update("size")
                .set(fields)
                .where(Expr("id").equals({":id"}))
                .build();
        query = exec(sql, QVariant::fromValue<int>(entity.getId()));
    }

    result = entityMapper.size(query);
    if (result.isLeft()) {
        QSqlDatabase::database().rollback();
    } else {
        QSqlDatabase::database().commit();
    }

    return result;
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
    exec(sql, QVariant::fromValue<int>(entity.getId()));
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
