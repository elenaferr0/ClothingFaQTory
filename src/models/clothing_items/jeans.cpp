#include "jeans.h"
#include "../../utils/calculator.h"

using Models::ClothingItems::Jeans;
using Models::Material;
using Utils::Calculator;

Jeans::Jeans(long id,
             string code,
             string color,
             Material material,
             Size size,
             int availableQuantity,
             int soldQuantity,
             string description,
             bool sustainableMaterials,
             string gender,
             bool shorts)
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
          shorts(shorts) {}

Jeans* Jeans::clone() const {
    return new Jeans(*this);
}

double Jeans::computePrice() const {
    // the surface of jeans is estimated with 2 cilinders
    double computedLength = computeLegLength();
    double computedWidth = computeLegWidth();

    double legLength = shorts ? computedLength / 2 : computedLength;

    double surface = 2 * Calculator::computeCilinderSurface(computedWidth, legLength);

    return surface * material.getCostPerUnit();
}

bool Jeans::areShorts() const {
    return shorts;
}

void Jeans::setShorts(bool shorts) {
    Jeans::shorts = shorts;
}

void Jeans::accept(IProductVisitor& visitor) {
    visitor.visitJeans(*this);
}

