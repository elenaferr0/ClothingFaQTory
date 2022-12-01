#include "bracelet.h"
#include "src/models/material.h"
#include "src/utils/calculator.h"

using Models::Material;
using Models::Accessories::Bracelet;
using Utils::Calculator;

Bracelet::Bracelet(string color, list<Material> materials, unsigned int pearlNumber, double pearlDiameter, int availableQuantity, int soldQuantity)
  : Accessory(color, materials, availableQuantity, soldQuantity), pearlNumber(pearlNumber), pearlDiameter(pearlDiameter){}

Bracelet* Bracelet::clone() const {
  return new Bracelet(*this);
}

double Bracelet::computePrice() const {
  double pearlVolume = Calculator::computeSphereVolume(pearlDiameter / 2);

  // first assumption: the material of the bracelet is either of GOLD, SILVER or WOOD
  // second assumption: each pearl can only be made of a single material
  Material material = Accessory::getMaterials().front();

  double specificWeight;
  switch (material.getName()){
    case Material::GOLD:
      specificWeight = Material::GOLD_SPECIFIC_WEIGHT;
      break;
    case Material::SILVER:
      specificWeight = Material::SILVER_SPECIFIC_WEIGHT;
      break;
    case Material::WOOD:
    default: // fallback
      specificWeight = Material::WOOD_SPECIFIC_WEIGHT;
    }

  double totalWeight = specificWeight * (pearlVolume * pearlNumber);

  return totalWeight * material.getCostPerUnit();
}
