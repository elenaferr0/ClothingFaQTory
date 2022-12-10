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

Material::UnitOfMeasure Material::getUnitOfMeasure() const {
    return unitOfMeasure;
}

double Material::getCostPerUnit() const {
    return costPerUnit;
}

void Material::setName(string name) {
    this->name = namefromString(name);
}

void Material::setUnitOfMeasure(string unitOfMeasure) {
    this->unitOfMeasure = unitOfMeasureFromString(unitOfMeasure);
}

void Material::setCostPerUnit(double costPerUnit) {
    this->costPerUnit = costPerUnit;
}

string Material::getTableName() const {
    return "material";
}

string Material::getNameAsString() const {
    switch (name) {
        case DENIM:
            return "DENIM";
        case WOOL:
            return "WOOL";
        case POLYESTER:
            return "POLYESTER";
        case COTTON:
            return "COTTON";
        case GOLD:
            return "GOLD";
        case SILVER:
            return "SILVER";
        case WOOD:
        default:
            return "WOOD";
    }
}

string Material::getUnitOfMeasureAsString() const {
    switch (unitOfMeasure) {
        case CENTIMETER:
            return "cm";
        case GRAM:
        default:
            return "g";
    }
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
        qWarning() << QString::fromStdString("Invalid name provided " + name + " for material");
        return POLYESTER;
    }
}

Material::UnitOfMeasure Models::Material::unitOfMeasureFromString(const string& unit) {
    if (unit == "cm") {
        return CENTIMETER;
    } else if (unit == "g") {
        return GRAM;
    } else {
        qWarning() << QString::fromStdString("Invalid unit of measure "  + unit + " provided for material");
        return CENTIMETER;
    }
}
