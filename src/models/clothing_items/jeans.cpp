#include "jeans.h"
#include "src/utils/calculator.h"
#include "src/models/material.h"

using Models::ClothingItems::Jeans;
using Models::Material;
using Utils::Calculator;

Jeans::Jeans(string color, list<Material> materials, Size size, int availableQuantity,
	     int soldQuantity, bool sustainableMaterials, bool shorts)
  : ClothingItem(color, materials, size, availableQuantity, soldQuantity, sustainableMaterials),
    shorts(shorts){}

Jeans* Jeans::clone() const {
  return new Jeans(*this);
}

double Jeans::computePrice() const{
  // the surface of jeans is estimated with 2 cilinders
  double computedLength = computeLegLength();
  double computedWidth = computeLegWidth();

  double legLength = shorts ?  computedLength / 2 : computedLength;

  double surface = 2 * Calculator::computeCilinderSurface(computedWidth, legLength);

  return surface * getMaterials().front().getCostPerUnit();
}
