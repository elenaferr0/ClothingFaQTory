#include "hat.h"

using Models::Accessories::Hat;

Hat::Hat(unsigned long id,
         string code,
         string color,
         list <Material> materials,
         Size size,
         int availableQuantity,
         int soldQuantity,
         string description,
	 Category category,
         bool isBaseballHat)
        : Accessory(id,
                    code,
                    color,
                    materials,
                    size,
                    availableQuantity,
                    soldQuantity,
		    description,
		    category),
	  isBaseballHat(isBaseballHat){};

Hat* Hat::clone() const {
    return new Hat(*this);
}

double Hat::computePrice() const {
  return 0;
}
