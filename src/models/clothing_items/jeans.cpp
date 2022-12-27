#include "jeans.h"
#include "../../utils/calculator.h"

using Models::ClothingItems::Jeans;
using Models::Material;
using Utils::Calculator;

Jeans::Jeans(int id,
             const string& code,
             const string& color,
             const Material& material,
             const Size& size,
             int availableQuantity,
             int soldQuantity,
             const string& description,
             bool sustainableMaterials,
             const string& gender,
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

double Jeans::computePrice() const {
    // the surface of jeans is estimated with 2 cilinders
    double computedLength = computeLegLength();
    double computedWidth = computeLegWidth();

    double legLength = shorts ? computedLength / 2 : computedLength;

    double surface = 2 * Calculator::computeCilinderSurface(computedWidth, legLength);
    Calculator::squaredCmToSquaredMeters(surface);

    return surface * material.getCostPerUnit();
}

const bool& Jeans::areShorts() const {
    return shorts;
}

void Jeans::setShorts(bool shorts) {
    Jeans::shorts = shorts;
}

void Jeans::accept(VisitorInterface& visitor) {
    visitor.visitJeans(*this);
}

