#ifndef SWEATER_H
#define SWEATER_H
#include "src/models/clothing_items/clothingitem.h"

namespace Models::ClothingItems {
  class Sweater : public ClothingItem
  {
    public:
      Sweater();
      Sweater* clone() const override;
      double computePrice() const override;
  };
}

#endif // SWEATER_H
