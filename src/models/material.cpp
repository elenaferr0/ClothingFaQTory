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

Material::Name Material::getName() const {
    return name;
}

double Material::getCostPerUnit() const {
    return costPerUnit;
}

Material::Name Models::Material::namefromString(const string& name) {
    if (name == "DENIM") {
        return DENIM;
    } else if (name == "WOOL") {
        return WOOL;
    } else if (name == "POLYESTER") {
        return POLYESTER;
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
        return CENTIMETER;
    }
}
