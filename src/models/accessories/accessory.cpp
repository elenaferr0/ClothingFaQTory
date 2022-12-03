#include "accessory.h"
#include "src/models/product.h"
#include<string>

using Models::Accessory;
using Models::Product;
using std::string;

Accessory::Accessory(
        unsigned long id,
        string code,
        string color,
        list <Material> materials,
        Size size,
        int availableQuantity,
        int soldQuantity,
        string description,
        Category category)
        : Product(id,
                  code,
                  color,
                  materials,
                  size,
                  availableQuantity,
                  soldQuantity,
                  description),
          category(category) {}
