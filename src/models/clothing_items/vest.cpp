#include "vest.h"
#include "clothing_item.h"
#include "../../utils/calculator.h"
#include <string>

using Models::ClothingItems::Vest;
using Utils::Calculator;
using std::string;

Vest::Vest(long id,
           string code,
           string color,
           Material material,
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
                       material,
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

    // TODO: add the cost of the buttons if present
    return material.getCostPerUnit() * surface;
}

string Vest::getTableName() const {
    return "vest";
}