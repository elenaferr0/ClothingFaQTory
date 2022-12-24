#include "vest_repository.h"
#include "crud_repository.h"
#include <QSqlRecord>

using Services::VestRepository;

VestRepository* VestRepository::instance;

VestRepository::VestRepository()
        : Repository("vest"), CRUDRepository("vest", EntityMapper::vest) {};

Either<Error, Vest> VestRepository::save(Vest& entity) {
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
            "has_buttons"
    };

    QVariantList params; // id will later be added only if the entity should be updated
    params << QString::fromStdString(entity.getCode())
           << QString::fromStdString(entity.getColor())
           << entity.getSoldQuantity()
           << entity.getAvailableQuantity()
           << QString::fromStdString(entity.getDescription())
           << entity.getSize().getId()
           << entity.hasSustainableMaterials()
           << QString::fromStdString(Vest::getGenderAsString(entity.getGender()))
           << entity.getMaterial().getId()
           << entity.getHasButtons();

    return CRUDRepository<Vest>::save(fields, params, entity);
}

VestRepository* VestRepository::getInstance() {
    if (instance == nullptr) {
        instance = new VestRepository();
    }
    return instance;
}