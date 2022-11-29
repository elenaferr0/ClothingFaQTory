#ifndef TSHIRT_H
#define TSHIRT_H
#include "src/models/clothing_items/clothingitem.h"

namespace Models::ClothingItems {
  class TShirt : public virtual ClothingItem
  {
    public:
      TShirt();
      double computePrice() const override;
      TShirt* clone() const override;
  };

}
#endif // TSHIRT_H
