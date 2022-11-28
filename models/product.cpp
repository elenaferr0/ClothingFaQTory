#include "models/product.h"
#include "models/material.h"
#include <string>

using std::string;
using Models::Product;
using Models::Material;

Product::Product(string color, list<Material> materials, Size size)
  : color(color), materials(materials), size(size){};

list<Material> Product::getMaterials() const {
  return materials;
}
