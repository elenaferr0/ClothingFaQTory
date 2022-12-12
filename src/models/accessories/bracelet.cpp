#include "bracelet.h"
#include "../../utils/calculator.h"

using Models::Material;
using Models::Accessories::Bracelet;
using Utils::Calculator;

Bracelet::Bracelet(
        long id,
        string code,
        string color,
        Material material,
        Size size,
        int availableQuantity,
        int soldQuantity,
        string description,
        string category,
        unsigned int pearlNumber,
        double pearlDiameter)
        : Accessory(id,
                    code,
                    color,
                    material,
                    size,
                    availableQuantity,
                    soldQuantity,
                    description,
                    category),
          pearlNumber(pearlNumber),
          pearlDiameter(pearlDiameter) {}

Bracelet* Bracelet::clone() const {
    return new Bracelet(*this);
}

double Bracelet::computePrice() const {
    double pearlVolume = Calculator::computeSphereVolume(pearlDiameter / 2);

    // first assumption: the material of the bracelet is either of GOLD, SILVER or WOOD
    // second assumption: each pearl can only be made of a single material

    double specificWeight;
    switch (material.getName()) {
        case Material::GOLD:
            specificWeight = Material::GOLD_SPECIFIC_WEIGHT;
            break;
        case Material::SILVER:
            specificWeight = Material::SILVER_SPECIFIC_WEIGHT;
            break;
        case Material::WOOD:
        default: // fallthrough
            specificWeight = Material::WOOD_SPECIFIC_WEIGHT;
    }

    double totalWeight = Calculator::computeWeightFrom(pearlVolume * pearlVolume, specificWeight);

    return totalWeight * material.getCostPerUnit();
}

unsigned int Bracelet::getPearlNumber() const {
    return pearlNumber;
}

double Bracelet::getPearlDiameter() const {
    return pearlDiameter;
}

void Bracelet::accept(IProductVisitor& visitor) {
    visitor.visitBracelet(*this);
}
