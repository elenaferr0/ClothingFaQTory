#include "src/models/accessories/backpack.h"
#include "src/utils/calculator.h"

using Models::Accessories::BackPack;
using Utils::Calculator;
const double BackPack::BACKPACK_HEIGHT = 30;
const double BackPack::BACKPACK_WIDTH = 20;

BackPack::BackPack(long id,
                   string code,
                   string color,
                   list <Material> materials,
                   Size size,
                   int availableQuantity,
                   int soldQuantity,
                   string description,
                   Category category,
                   double capacity)
        : Accessory(id,
                    code,
                    color,
                    materials,
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

    // if the backpack is made of different material, we suppose that
    // the percentage of the composition is the same for each of them

    int nMaterials = materials.size();

    double price = 0;
    for (auto i = materials.begin(); i != materials.end(); i++) {
        price += (*i).getCostPerUnit() * surface / nMaterials;
    }

    return price;
}

string BackPack::getTableName() const {
    return "backpack";
}
