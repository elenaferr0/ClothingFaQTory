#ifndef JEANS_H
#define JEANS_H
#include "src/models/clothing_items/clothingitem.h"
#include<list>
using std::list;

namespace Models::ClothingItems {
class Jeans : public virtual ClothingItem
{
  private:
    // if shorts is true, when calculating the price half the length will be used
    bool shorts;
  public:
    Jeans(string color = "", list<Material> materials = list<Material>(), Size size = Size(), int availableQuantity = 0,
	  int soldQuantity = 0, bool sustainableMaterials = false, bool shorts = false);
    double computePrice() const override;
    Jeans* clone() const override;
};
}

#endif // JEANS_H
