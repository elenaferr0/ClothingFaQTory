#include "material_repository.h"
#include "crud_repository.h"
#include <list>
#include <QDebug>
#include <QSqlRecord>
#include <QSqlQuery>

using std::list;
using Models::Material;
using Services::MaterialRepository;
using Services::CRUDRepository;
using Core::Error;
using Core::Db::Expr;

MaterialRepository* MaterialRepository::instance;

MaterialRepository::MaterialRepository()
        : ReadOnlyRepository("material", entityMapper.material) {};

Either<Error, Material> MaterialRepository::findById(int id) {
    if (materials.hasKey(id)) {
        return materials.get(id).value();
    }

    string sql = queryBuilder.select()
            .from(table)
            .where(Expr("id").equals({"?"}))
            .build();
    QSqlQuery query = exec(sql, QVariant::fromValue<int>(id));
    query.next(); // is needed so the record can be read
    Either<Error, Material> errorOrMaterial = entityMapper.material(query);

    if (errorOrMaterial.isLeft()) {
        qCritical() << QString::fromStdString(
                errorOrMaterial.forceLeft().getMessage());
    }

    materials[id] = errorOrMaterial.forceRight();
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
            qCritical() << QString::fromStdString(materialOrError.forceLeft().getMessage());
            return materialOrError.forceLeft();
        }
        materials.push_back(materialOrError.forceRight());
    }
    return materials;
}

MaterialRepository* Services::MaterialRepository::getInstance() {
    if (instance == nullptr) {
        instance = new MaterialRepository();
    }
    return instance;
}

Either<Error, Material> Services::MaterialRepository::findByName(const Material::Name& name) {
    return findById(name);
}


Either<Error, Material> MaterialRepository::saveCostPerUnit(const Material& entity) {

    QVariantList params;
    params << entity.getCostPerUnit()
           << entity.getId();

    string sql = queryBuilder.update(entity.getTableName())
            .set("cost_per_unit")
            .where(Expr("id").equals({"?"}))
            .build();

    QSqlQuery query = exec(sql, params);
    query.next();

    optional<Error> hasError = ReadOnlyRepository::hasError(query);

    if (hasError.has_value()) {
        qCritical() << QString::fromStdString(
                hasError.value().getMessage());
        return Either<Error, Material>::ofLeft(hasError.value());
    }

    return entity;
}
