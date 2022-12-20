
#include "backpack.h"
#include "../../utils/calculator.h"
#include <list>

using std::list;
using Models::Accessories::BackPack;
using Utils::Calculator;
const double BackPack::BACKPACK_HEIGHT = 30;
const double BackPack::BACKPACK_WIDTH = 20;

BackPack::BackPack(long id,
                   string code,
                   string color,
                   Material material,
                   Size size,
                   int availableQuantity,
                   int soldQuantity,
                   string description,
                   string category,
                   double capacity)
        : Accessory(id,
                    code,
                    color,
                    material,
                    size,
                    availableQuantity,
                    soldQuantity,
                    description,
                    category),
          capacity(capacity) {};

BackPack* BackPack::clone() const {
    return new BackPack(*this);
}

double BackPack::computePrice() const {
    // calculate the depth dividing the volume (capacity) by height and width
    double backpackDepth = capacity / (BACKPACK_HEIGHT * BACKPACK_WIDTH);
    double surface = Calculator::computeTrapezoidalBasedPrismSurfaceFrom(BACKPACK_HEIGHT, backpackDepth);
    Calculator::squaredCmToSquaredMeters(surface);

    return material.getCostPerUnit() * surface;
}

const double& BackPack::getCapacity() const {
    return capacity;
}

void BackPack::accept(ModelVisitorInterface& visitor) {
    visitor.visitBackPack(*this);
}
