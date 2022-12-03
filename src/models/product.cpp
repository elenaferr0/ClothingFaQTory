#include "src/models/product.h"
#include "src/models/material.h"
#include <string>

using std::string;
using Models::Product;
using Models::Material;

Product::Product(unsigned long id,
                 string code,
                 string color,
                 list <Material> materials,
                 Size size,
                 int availableQuantity,
                 int soldQuantity,
                 string description)
        : Model(id),
          code(code),
          color(color),
          materials(materials),
          size(size),
          availableQuantity(availableQuantity),
          soldQuantity(soldQuantity),
          description(description){};
