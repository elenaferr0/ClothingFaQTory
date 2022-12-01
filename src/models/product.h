#ifndef PRODUCT_H
#define PRODUCT_H
#include "src/models/material.h"
#include "src/models/size.h"
#include "src/core/model.h"

#include<string>
#include<list>

using std::string;
using std::list;
using Core::Model;

namespace Models {
  class Product : public Model
  {
    protected:
      string color;
      list<Material> materials;
      Size size;
      int availableQuantity;
      int soldQuantity;

    public:
      virtual list<Material> getMaterials() const;
      Product(string color = "", list<Material> materials = list<Material>(), Size size = Size(), int availableQuantity = 0, int soldQuantity = 0);
      virtual double computePrice() const = 0;
      virtual ~Product(){};
  };
}
#endif // PRODUCT_H
