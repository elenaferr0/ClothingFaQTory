#include "jeans.h"
#include "src/utils/calculator.h"
#include "src/models/material.h"

using Models::ClothingItems::Jeans;
using Models::Material;
using Utils::Calculator;

Jeans::Jeans(string color, Material material, Size size, bool shorts)
  : ClothingItem(color, list(1, material), size, shorts),
    shorts(shorts){}

Jeans* Jeans::clone() const {
  return new Jeans(*this);
}

double Jeans::computePrice() const{
  // the surface of jeans is estimated with 2 cilinders
  double legLength = shorts ? length / 2 :  length;

  double surface = 2 * Calculator::computeCilinderSurface(width, legLength);


}
