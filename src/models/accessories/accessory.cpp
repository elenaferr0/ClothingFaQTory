#include "accessory.h"
#include "src/models/product.h"
#include<string>

using Models::Accessory;
using Models::Product;
using std::string;

Accessory::Accessory(string color, list<Material> materials,int availableQuantity, int soldQuantity)
  :Product(color, materials, Size::ONE_SIZE, availableQuantity, soldQuantity){}
