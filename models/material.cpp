#include "material.h"

using Models::Material;

const double Material::GOLD_SPECIFIC_WEIGHT = 19.32;
const double Material::SILVER_SPECIFIC_WEIGHT = 10.490;
const double Material::WOOD_SPECIFIC_WEIGHT = 0.750;

Material::Material(Material::Name name, Material::UnitOfMeasure unitOfMeasure, double costPerUnit)
  : name(name), unitOfMeasure(unitOfMeasure), costPerUnit(costPerUnit){};
