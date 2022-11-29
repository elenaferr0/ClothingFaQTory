#ifndef OVERALLS_H
#define OVERALLS_H
#include "src/models/clothing_items/tshirt.h"
#include "src/models/clothing_items/jeans.h"

namespace Models::ClothingItems {
  class Overalls: public TShirt, public Jeans
  {
    public:
      Overalls();
      double computePrice() const override;
      Overalls* clone() const override;
  };
}

#endif // OVERALLS_H
