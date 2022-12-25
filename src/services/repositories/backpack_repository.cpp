#include "backpack_repository.h"

using Services::BackPackRepository;

BackPackRepository* BackPackRepository::instance;

BackPackRepository::BackPackRepository()
        : Repository("backpack"), CRUDRepository("backpack", EntityMapper::backPack) {};

Either<Error, BackPack*> BackPackRepository::save(BackPack* entity) {

    list<string> fields = {
            "code",
            "color",
            "sold_quantity",
            "available_quantity",
            "description",
            "size_id",
            "category",
            "capacity",
            "material_id"
    };

    QVariantList params; // id will later be added only if the entity should be updated
    params << QString::fromStdString(entity->getCode())
           << QString::fromStdString(entity->getColor())
           << entity->getSoldQuantity()
           << entity->getAvailableQuantity()
           << QString::fromStdString(entity->getDescription())
           << entity->getSize().getId()
           << QString::fromStdString(BackPack::getCategoryAsString(entity->getCategory()))
           << entity->getCapacity()
           << entity->getMaterial().getId();

    return CRUDRepository<BackPack>::save(fields, params, entity);
}

BackPackRepository* BackPackRepository::getInstance() {
    if (instance == nullptr) {
        instance = new BackPackRepository();
    }
    return instance;
}