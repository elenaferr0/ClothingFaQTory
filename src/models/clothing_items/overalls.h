#ifndef OVERALLS_H
#define OVERALLS_H
#include "src/models/clothing_items/vest.h"
#include "src/models/clothing_items/jeans.h"

namespace Models::ClothingItems {
  class Overalls: public Vest, public Jeans
  {
    public:
      Overalls(unsigned long id = 0,
               string code = "",
               string color = "",
               list <Material> materials = list<Material>(),
               Size size = Size(),
               int availableQuantity = 0,
               int soldQuantity = 0,
               string description = "",
               bool sustainableMaterials = false,
               Gender gender = Gender::UNISEX,
               bool shorts = false,
               bool hasButtons = false);
      double computePrice() const override;
      Overalls* clone() const override;
  };
}

#endif // OVERALLS_H
