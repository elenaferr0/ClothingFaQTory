#include "hat.h"
#include "src/utils/calculator.h"

using Models::Accessories::Hat;
using Utils::Calculator;

Hat::Hat(long id,
         string code,
         string color,
         list <Material> materials,
         Size size,
         int availableQuantity,
         int soldQuantity,
         string description,
         Category category,
         bool isBaseballCap)
        : Accessory(id,
                    code,
                    color,
                    materials,
                    size,
                    availableQuantity,
                    soldQuantity,
                    description,
                    category),
          isBaseballCap(isBaseballCap) {};

Hat* Hat::clone() const {
    return new Hat(*this);
}

double Hat::computePrice() const {
    // the cost of the hat is estimated through the surface of half a sphere
    // if it's a baseball hat, the cost of the visor part surface is added.
    double surface = Calculator::computeSphereSurface(DIAMETER / 2) / 2;

    if (isBaseballCap) {
        surface += Calculator::computeRectangleArea(VISOR_LENGTH, VISOR_WIDTH);
    }

    double price = 0;
    for (auto i = materials.begin(); i != materials.end(); i++) {
        price += (*i).getCostPerUnit() * surface / materials.size();
    }

    return price;
}

string Hat::getTableName() const {
    return "hat";
}