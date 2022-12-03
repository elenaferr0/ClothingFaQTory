#include "material.h"

using Models::Material;

const double Material::GOLD_SPECIFIC_WEIGHT = 19.32;
const double Material::SILVER_SPECIFIC_WEIGHT = 10.490;
const double Material::WOOD_SPECIFIC_WEIGHT = 0.750;

Material::Material(
    unsigned long id,
    Material::Name name,
    Material::UnitOfMeasure unitOfMeasure,
    double costPerUnit)
  : Model(id),
    name(name),
    unitOfMeasure(unitOfMeasure),
    costPerUnit(costPerUnit){};

Material* Material::clone() const {
  return new Material(*this);
}

Material::Name Material::getName() const {
  return name;
}

double Material::getCostPerUnit() const {
  return costPerUnit;
}

string Material::getTableName() const {
    return "material";
}