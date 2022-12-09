#include "material_repository.h"
#include "crud_repository.h"
#include "../../models/material.h"
#include "../../core/errors/error.h"
#include "../../core/db/expression.h"
#include <list>
#include <QDebug>

using std::list;
using Models::Material;
using Services::MaterialRepository;
using Services::CRUDRepository;
using Core::Error;
using Core::Db::Expr;

MaterialRepository::MaterialRepository()
        : ReadOnlyRepository("material") {};

Either<Error, Material> MaterialRepository::findById(int id) {
    string sql = queryBuilder.select()
            .from(table)
            .where(Expr("id").equals({"?"}))
            .build();
    QSqlQuery query = exec(sql, QVariant::fromValue<int>(id));
    query.next(); // is needed so the record can be read
    Either<Error, Material> errorOrMaterial = entityMapper.material(query);

    if (errorOrMaterial.isLeft()) {
        qCritical() << QString::fromStdString(
                errorOrMaterial.left().value().getMessage());
    }
    return errorOrMaterial;
}

Either<Error, list<Material>> MaterialRepository::findAll() {
    string sql = queryBuilder.select()
            .from(table)
            .build();
    QSqlQuery query = exec(sql);
    list<Material> materials;
    while (query.next()) {
        Either<Error, Material> materialOrError = entityMapper.material(query);
        if (materialOrError.isLeft()) {
            qCritical() << QString::fromStdString(materialOrError.left().value().getMessage());
            return materialOrError.left().value();
        }
        materials.push_back(materialOrError.right().value());
    }
    return materials;
}
