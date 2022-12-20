#include "material.h"
#include <QDebug>

using Models::Material;

const double Material::GOLD_SPECIFIC_WEIGHT = 19.32;
const double Material::SILVER_SPECIFIC_WEIGHT = 10.490;
const double Material::WOOD_SPECIFIC_WEIGHT = 0.750;

Material::Material(
        long id,
        string name,
        string unitOfMeasure,
        double costPerUnit)
        : Model(id),
          name(namefromString(name)),
          unitOfMeasure(unitOfMeasureFromString(unitOfMeasure)),
          costPerUnit(costPerUnit) {};

Material* Material::clone() const {
    return new Material(*this);
}

const Material::Name& Material::getName() const {
    return name;
}

const double& Material::getCostPerUnit() const {
    return costPerUnit;
}

Material::Name Models::Material::namefromString(const string& name) {
    if (name == "DENIM") {
        return DENIM;
    } else if (name == "WOOL") {
        return WOOL;
    } else if (name == "COTTON") {
        return COTTON;
    } else if (name == "GOLD") {
        return GOLD;
    } else if (name == "SILVER") {
        return SILVER;
    } else if (name == "WOOD") {
        return WOOD;
    } else {
        return POLYESTER;
    }
}

Material::UnitOfMeasure Models::Material::unitOfMeasureFromString(const string& unit) {
    if (unit == "g") {
        return GRAM;
    } else {
        return METER;
    }
}

string Models::Material::getUnitOfMeasureAsString() const {
    switch (unitOfMeasure) {
        case GRAM:
            return "g";
        case METER:
        default:
            return "m";
    }
}

string Models::Material::getNameAsString() const {
    switch (name) {
        case DENIM:
            return "DENIM";
        case WOOL:
            return "WOOL";
        case COTTON:
            return "COTTON";
        case GOLD:
            return "GOLD";
        case SILVER:
            return "SILVER";
        case WOOD:
            return "WOOD";
        case POLYESTER:
        default:
            return "POLYESTER";
    }
}

void Models::Material::accept(ModelVisitorInterface& visitor) {
    visitor.visitMaterial(*this);
}
