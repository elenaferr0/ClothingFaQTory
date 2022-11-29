#ifndef JEANS_H
#define JEANS_H
#include "src/models/clothing_items/clothingitem.h"

namespace Models::ClothingItems {
  class Jeans : public virtual ClothingItem
  {
    public:
      Jeans();
      double computePrice() const override;
      Jeans* clone() const override;
  };
}

#endif // JEANS_H
