#include "material.h"

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
          name(name),
          unitOfMeasure(unitOfMeasure),
          costPerUnit(costPerUnit) {};

Material* Material::clone() const {
    return new Material(*this);
}

string Material::getName() const {
    return name;
}

string Material::getUnitOfMeasure() const {
  return name;
}

double Material::getCostPerUnit() const {
    return costPerUnit;
}

void Material::setName(string name){
  this->name = name;
}

void Material::setUnitOfMeasure(string unitOfMeasure){
  this->unitOfMeasure = unitOfMeasure;
}

void Material::setCostPerUnit(double costPerUnit){
  this->costPerUnit = costPerUnit;
}

string Material::getTableName() const {
    return "material";
}
