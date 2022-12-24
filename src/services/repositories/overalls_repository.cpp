#include "overalls_repository.h"
#include "crud_repository.h"
#include <QSqlRecord>

using Services::OverallsRepository;

OverallsRepository* OverallsRepository::instance;

OverallsRepository::OverallsRepository()
        : Repository("overalls"), CRUDRepository("overalls", EntityMapper::overalls) {};

Either<Error, Overalls> OverallsRepository::save(Overalls& entity) {

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
            "has_buttons",
            "shorts"
    };

    QVariantList params; // id will later be added only if the entity should be updated
    params << QString::fromStdString(entity.getCode())
           << QString::fromStdString(entity.getColor())
           << entity.getSoldQuantity()
           << entity.getAvailableQuantity()
           << QString::fromStdString(entity.getDescription())
           << entity.getSize().getId()
           << entity.hasSustainableMaterials()
           << QString::fromStdString(Overalls::getGenderAsString(entity.getGender()))
           << entity.getMaterial().getId()
           << entity.getHasButtons()
           << entity.areShorts();

    return CRUDRepository<Overalls>::save(fields, params, entity);
}

OverallsRepository* OverallsRepository::getInstance() {
    if (instance == nullptr) {
        instance = new OverallsRepository();
    }
    return instance;
}