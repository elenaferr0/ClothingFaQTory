#ifndef CLOTHINGITEM_H
#define CLOTHINGITEM_H
#include "src/models/product.h"

namespace Models {
  class ClothingItem : public Product
  {
    private:
      double computeLength(bool, Size) const;
      double computeWidth(bool, Size) const;

    protected:
      double length;
      double width;

    public:
      // constants used for top part clothing
      static const double SMALLEST_SIZE_TRUNK_WIDTH;
      static const double SMALLEST_SIZE_TRUNK_LENGTH;

      // constants used for bottom part clothing
      static const double SMALLEST_SIZE_LEG_WIDTH;
      static const double SMALLEST_SIZE_LEG_LENGTH;
      ClothingItem(string color, list<Material> materials, Size size, bool isTopClothingItem);
  };
}

#endif // CLOTHINGITEM_H
