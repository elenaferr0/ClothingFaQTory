#include "material_repository.h"
#include "crud_repository.h"
#include <QDebug>
#include <QSqlRecord>
#include <QSqlQuery>

using Models::Material;
using Services::MaterialRepository;
using Services::CRUDRepository;
using Core::Error;
using Core::Db::Expr;

MaterialRepository* MaterialRepository::instance;

MaterialRepository::MaterialRepository()
        : Repository("material"), ReadOnlyRepository("material", EntityMapper::material) {};

Either<Error, Material*> MaterialRepository::findById(int id) {
    if (cachedMaterials.hasKey(id)) {
        return cachedMaterials.get(id).value();
    }

    Either<Error, Material*> errorOrMaterial = ReadOnlyRepository::findById(id);

    cachedMaterials.put(id, errorOrMaterial.forceRight());
    return errorOrMaterial;
}

Either<Error, LinkedList<Material*>> MaterialRepository::findAll() {
    Either<Error, LinkedList<Material*>> materialsOrError = ReadOnlyRepository::findAll();
    if (materialsOrError.isRight()) {
        for (auto m: materialsOrError.forceRight()) {
            cachedMaterials.put(m->getId(), m);
        }
    }
    return materialsOrError;
}

Either<Error, Material*> Services::MaterialRepository::findByName(const Material::Name& name) {
    return findById(name);
}


Either<Error, Material*> MaterialRepository::saveCostPerUnit(Material* entity) {

    LinkedList<QVariant> params = {entity->getCostPerUnit(), entity->getId()};

    string sql = queryBuilder.update(table)
            .set("cost_per_unit")
            .where(Expr("id").equals({"?"}))
            .build();

    QSqlQuery query = exec(sql, params);
    query.next();

    optional<Error> hasError = ReadOnlyRepository::hasError(query);

    if (hasError.has_value()) {
        qCritical() << QString::fromStdString(
                hasError.value().getCause());
        return Either<Error, Material*>::ofLeft(hasError.value());
    }

    if (cachedMaterials.hasKey(entity->getId())) {
        cachedMaterials.get(entity->getId()).value()->setCostPerUnit(entity->getCostPerUnit());
    }
    return entity;
}

MaterialRepository* Services::MaterialRepository::getInstance() {
    if (instance == nullptr) {
        instance = new MaterialRepository();
    }
    return instance;
}

Services::MaterialRepository::~MaterialRepository() {
    for (auto it = cachedMaterials.cbegin(); it != cachedMaterials.cend(); it++) {
        delete (*it).second;
    }
}
