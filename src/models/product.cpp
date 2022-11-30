#include "src/models/product.h"
#include "src/models/material.h"
#include <string>

using std::string;
using Models::Product;
using Models::Material;

Product::Product(string color, list<Material> materials, Size size, int availableQuantity, int soldQuantity)
  : color(color), materials(materials), size(size), availableQuantity(availableQuantity), soldQuantity(soldQuantity){};

list<Material> Product::getMaterials() const {
  return materials;
}
