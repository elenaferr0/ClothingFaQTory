#include "tshirt.h"
#include "src/utils/calculator.h"

using Models::ClothingItems::TShirt;
using Utils::Calculator;

TShirt::TShirt(string color, list<Material> materials,
	       Size size, int availableQuantity,
	       int soldQuantity, bool sustainableMaterials)
  :ClothingItem(color, materials, size, availableQuantity, soldQuantity, sustainableMaterials){}

TShirt* TShirt::clone() const {
  return new TShirt(*this);
}

double TShirt::computePrice() const {
  double trunkLength = ClothingItem::computeTrunkLength();
  double trunkWidth = ClothingItem::computeTrunkWidth();

  /*
   * the surface of the tshirt is estimated with the surface of three cilinders
   * 2 for the sleeves (which are supposedly 1/4 of the height and 1/4 of the
   * width of the body
   */
  double surface =
      2 * Calculator::computeCilinderSurface(trunkWidth / 8, trunkLength / 4) + // sleeves
      Calculator::computeCilinderSurface(trunkWidth / 2, trunkLength);

  list<Material> materials = getMaterials();

  int nMaterials = materials.size();

  double price = 0;
  for(auto i = materials.begin(); i != materials.end(); i++){
    price += (*i).getCostPerUnit() * surface / nMaterials;
  }

  return price;
}
