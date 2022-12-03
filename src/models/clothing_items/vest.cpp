#include "vest.h"
#include "src/utils/calculator.h"

using Models::ClothingItems::Vest;
using Utils::Calculator;

Vest::Vest(unsigned long id,
           string code,
           string color,
           list <Material> materials,
           Size size,
           int availableQuantity,
           int soldQuantity,
           string description,
           bool sustainableMaterials,
           Gender gender,
           bool hasButtons)
        : ClothingItem(id,
                       code,
                       color,
                       materials,
                       size,
                       availableQuantity,
                       soldQuantity,
                       description,
		       sustainableMaterials,
                       gender),
          hasButtons(hasButtons) {}

Vest* Vest::clone() const {
    return new Vest(*this);
}

double Vest::computePrice() const {
    double trunkLength = ClothingItem::computeTrunkLength();
    double trunkWidth = ClothingItem::computeTrunkWidth();

    // the surface of the Vest is estimated with the surface of a cilinder
    double surface = Calculator::computeCilinderSurface(trunkWidth, trunkLength);

    int nMaterials = materials.size();

    double price = 0;
    for (auto i = materials.begin(); i != materials.end(); i++) {
        price += (*i).getCostPerUnit() * surface / nMaterials;
    }

    // TODO: add the cost of the buttons if present

    return price;
}
