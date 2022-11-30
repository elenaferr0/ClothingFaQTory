#include "overalls.h"

using Models::ClothingItems::Overalls;

Overalls::Overalls(string color, list<Material> materials,
		   Size size, int availableQuantity,
		   int soldQuantity, bool sustainableMaterials)
  : ClothingItem(color, materials, size, availableQuantity, soldQuantity, sustainableMaterials),
    TShirt(), Jeans(color, materials.front(), size, false){

}

Overalls* Overalls::clone() const {
  return new Overalls(*this);
}

double Overalls::computePrice() const {
  return Jeans::computePrice() + TShirt::computePrice();
}
