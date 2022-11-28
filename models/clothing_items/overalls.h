#ifndef OVERALLS_H
#define OVERALLS_H
#include "models/clothing_items/tshirt.h"
#include "models/clothing_items/jeans.h"

namespace Models::ClothingItems {
  class Overalls: public TShirt, public Jeans
  {
    public:
      Overalls();
  };
}

#endif // OVERALLS_H
