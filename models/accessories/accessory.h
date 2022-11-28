#ifndef ACCESSORY_H
#define ACCESSORY_H
#include "models/product.h"

namespace Models {
  class Accessory : public Product
  {
    public:
      Accessory(string color, list<Material> materials);
  };
}
#endif // ACCESSORY_H
