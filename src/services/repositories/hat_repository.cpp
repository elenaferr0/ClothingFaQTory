#include "hat_repository.h"
#include "crud_repository.h"
#include <QSqlRecord>

using Services::HatRepository;

HatRepository* HatRepository::instance;

HatRepository::HatRepository()
        : Repository("hat"), CRUDRepository("hat", EntityMapper::hat) {};


Either<Error, Hat*> HatRepository::save(Hat* entity) {
    list<string> fields = {
            "code",
            "color",
            "size_id",
            "available_quantity",
            "sold_quantity",
            "description",
            "category",
            "is_baseball_hat",
            "material_id"
    };

    QVariantList params; // id will later be added only if the entity should be updated
    params << QString::fromStdString(entity->getCode())
           << QString::fromStdString(entity->getColor())
           << entity->getSize().getId()
           << entity->getAvailableQuantity()
           << entity->getSoldQuantity()
           << QString::fromStdString(entity->getDescription())
           << QString::fromStdString(Hat::getCategoryAsString(entity->getCategory()))
           << entity->isBaseballCap()
           << entity->getMaterial().getId();


    return CRUDRepository<Hat>::save(fields, params, entity);
}

HatRepository* Services::HatRepository::getInstance() {
    if (instance == nullptr) {
        instance = new HatRepository();
    }
    return instance;
}
