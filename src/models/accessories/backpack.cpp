
#include "backpack.h"
#include "../../utils/calculator.h"
using Models::Accessories::BackPack;
using Utils::Calculator;
const double BackPack::BACKPACK_HEIGHT = 30;
const double BackPack::BACKPACK_WIDTH = 20;

BackPack::BackPack(int id,
                   const string& code,
                   const string& color,
                   const Material& material,
                   const Size& size,
                   int availableQuantity,
                   int soldQuantity,
                   const string& description,
                   const string& category,
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

void BackPack::accept(VisitorInterface& visitor) {
    visitor.visitBackPack(*this);
}

void Models::Accessories::BackPack::setCapacity(double capacity) {
    this->capacity = capacity;
}
