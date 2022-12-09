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

    double price = 0;
    for (auto i = materials.begin(); i != materials.end(); i++) {
        price += (*i).getCostPerUnit() * surface / materials.size();
    }

    // TODO: add the cost of the buttons if present
    // suppose the buttons are made of polyester

    return price;
}

string Vest::getTableName() const {
    return "vest";
}