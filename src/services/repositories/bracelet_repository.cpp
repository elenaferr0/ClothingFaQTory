#include "bracelet_repository.h"

using Services::BraceletRepository;

BraceletRepository* BraceletRepository::instance;

BraceletRepository::BraceletRepository()
        : Repository("bracelet"), CRUDRepository("bracelet", EntityMapper::bracelet) {};

Either<Error, Bracelet*> BraceletRepository::save(Bracelet* entity) {

    list<string> fields = {
            "code",
            "color",
            "sold_quantity",
            "available_quantity",
            "description",
            "size_id",
            "category",
            "pearl_number",
            "pearl_diameter",
            "material_id"
    };

    QVariantList params; // id will later be added only if the entity should be updated
    params << QString::fromStdString(entity->getCode())
           << QString::fromStdString(entity->getColor())
           << entity->getSoldQuantity()
           << entity->getAvailableQuantity()
           << QString::fromStdString(entity->getDescription())
           << entity->getSize().getId()
           << QString::fromStdString(Bracelet::getCategoryAsString(entity->getCategory()))
           << entity->getPearlNumber()
           << entity->getPearlDiameter()
           << entity->getMaterial().getId();

    return CRUDRepository<Bracelet>::save(fields, params, entity);
}

BraceletRepository* BraceletRepository::getInstance() {
    if (instance == nullptr) {
        instance = new BraceletRepository();
    }
    return instance;
}