#include "hat.h"
#include "../../utils/calculator.h"
#include <string>

using std::string;
using Models::Accessories::Hat;
using Utils::Calculator;

const double Hat::DIAMETER = 13.2;
const double Hat::VISOR_LENGTH = 6.2;
const double Hat::VISOR_WIDTH = 3.10;

Hat::Hat(int id,
         const string& code,
         const string& color,
         const Material& material,
         const Size& size,
         int availableQuantity,
         int soldQuantity,
         const string& description,
         const string& category,
         bool isBaseballCap)
        : Accessory(id,
                    code,
                    color,
                    material,
                    size,
                    availableQuantity,
                    soldQuantity,
                    description,
                    category),
          baseballCap(isBaseballCap) {};

double Hat::computePrice() const {
    // the cost of the hat is estimated through the surface of half a sphere
    // if it's a baseball hat, the cost of the visor part surface is added.
    double surface = Calculator::computeSphereSurface(DIAMETER / 2) / 2;
    Calculator::squaredCmToSquaredMeters(surface);

    if (baseballCap) {
        surface += Calculator::computeRectangleArea(VISOR_LENGTH, VISOR_WIDTH);
    }

    return material.getCostPerUnit() * surface;
}

const bool& Hat::isBaseballCap() const {
    return baseballCap;
}

void Hat::accept(VisitorInterface& visitor) {
    visitor.visitHat(*this);
}

void Hat::setBaseballCap(bool baseballCap) {
    this->baseballCap = baseballCap;
}
