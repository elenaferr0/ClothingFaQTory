#include "jeans_repository.h"
#include "crud_repository.h"
#include <QSqlRecord>

using Services::JeansRepository;

JeansRepository* JeansRepository::instance;

JeansRepository::JeansRepository()
        : Repository("jeans"), CRUDRepository("jeans", EntityMapper::jeans) {};


Either<Error, Jeans*> JeansRepository::save(Jeans* entity) {

    list<string> fields = {
            "code",
            "color",
            "sold_quantity",
            "available_quantity",
            "description",
            "size_id",
            "sustainable_materials",
            "gender",
            "material_id",
            "shorts"
    };

    QVariantList params; // id will later be added only if the entity should be updated
    params << QString::fromStdString(entity->getCode())
           << QString::fromStdString(entity->getColor())
           << entity->getSoldQuantity()
           << entity->getAvailableQuantity()
           << QString::fromStdString(entity->getDescription())
           << entity->getSize().getId()
           << entity->hasSustainableMaterials()
           << QString::fromStdString(Jeans::getGenderAsString(entity->getGender()))
           << entity->getMaterial().getId()
           << entity->areShorts();


    return CRUDRepository<Jeans>::save(fields, params, entity);
}

JeansRepository* Services::JeansRepository::getInstance() {
    if (instance == nullptr) {
        instance = new JeansRepository();
    }
    return instance;
}
