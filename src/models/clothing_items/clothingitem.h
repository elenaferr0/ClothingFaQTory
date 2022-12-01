#ifndef CLOTHINGITEM_H
#define CLOTHINGITEM_H
#include "src/models/product.h"

namespace Models {
  class ClothingItem : public Product
  {
    protected:
      double computeLegLength() const;
      double computeTrunkLength() const;
      double computeLegWidth() const;
      double computeTrunkWidth() const;
      bool sustainableMaterials;
\
      // constants used for top part clothing
      static const double SMALLEST_SIZE_TRUNK_WIDTH;
      static const double SMALLEST_SIZE_TRUNK_LENGTH;

      // constants used for bottom part clothing
      static const double SMALLEST_SIZE_LEG_WIDTH;
      static const double SMALLEST_SIZE_LEG_LENGTH;

    public:
      ClothingItem(string color, list<Material> materials,
		   Size size, int availableQuantity,
		   int soldQuantity, bool sustainableMaterials = false);
  };
}

#endif // CLOTHINGITEM_H
