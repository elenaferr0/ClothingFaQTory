#include "hat.h"
#include "../../utils/calculator.h"
#include <string>
#include <list>

using std::string;
using std::list;
using Models::Accessories::Hat;
using Utils::Calculator;

const double Hat::DIAMETER = 15.5;
const double Hat::VISOR_LENGTH = 10.25;
const double Hat::VISOR_WIDTH = 5.25;

Hat::Hat(long id,
         string code,
         string color,
         list <Material> materials,
         Size size,
         int availableQuantity,
         int soldQuantity,
         string description,
	 string category,
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
	  baseballCap(isBaseballCap) {};

Hat* Hat::clone() const {
    return new Hat(*this);
}

double Hat::computePrice() const {
    // the cost of the hat is estimated through the surface of half a sphere
    // if it's a baseball hat, the cost of the visor part surface is added.
    double surface = Calculator::computeSphereSurface(DIAMETER / 2) / 2;

    if (baseballCap) {
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

bool Hat::isBaseballCap() const {
    return baseballCap;
}

void Hat::setIsBaseballCap(bool isBaseballCap) {
    isBaseballCap = isBaseballCap;
}
