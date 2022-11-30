#ifndef JEANS_H
#define JEANS_H
#include "src/models/clothing_items/clothingitem.h"

namespace Models::ClothingItems {
class Jeans : public virtual ClothingItem
{
  private:
    // if shorts is true, when calculating the price half the length will be used
    bool shorts;
  public:
    Jeans(string color, Material material, Size size, bool shorts);
    double computePrice() const override;
    Jeans* clone() const override;
};
}

#endif // JEANS_H
