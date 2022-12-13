#include "vest.h"
#include "clothing_item.h"
#include "../../utils/calculator.h"
#include <string>

using Models::ClothingItems::Vest;
using Utils::Calculator;
using std::string;

const unsigned int Vest::N_BUTTONS = 4;
const double Vest::BUTTON_DIAMETER = 1;

Vest::Vest(long id,
           string code,
           string color,
           Material material,
           Size size,
           int availableQuantity,
           int soldQuantity,
           string description,
           bool sustainableMaterials,
           string gender,
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

    double price = surface * material.getCostPerUnit();

    if (hasButtons) {
        // the volume of each button is half a wooden sphere
        double buttonVolume = Calculator::computeSphereVolume(BUTTON_DIAMETER / 2) / 2;
        double buttonWeight = Calculator::computeWeightFrom(buttonVolume, Material::WOOD_SPECIFIC_WEIGHT);

        price += N_BUTTONS * buttonWeight * material.getCostPerUnit();
    }
    return price;
}

bool Vest::getHasButtons() const {
    return hasButtons;
}

void Vest::accept(VisitorInterface& visitor) {
    visitor.visitVest(*this);
}
