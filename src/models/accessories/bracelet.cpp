#include "bracelet.h"
#include "../../utils/calculator.h"

using Models::Material;
using Models::Accessories::Bracelet;
using Utils::Calculator;

Bracelet::Bracelet(
        int id,
        const string& code,
        const string& color,
        const Material& material,
        const Size& size,
        int availableQuantity,
        int soldQuantity,
        const string& description,
        const string& category,
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

const unsigned int& Bracelet::getPearlNumber() const {
    return pearlNumber;
}

const double& Bracelet::getPearlDiameter() const {
    return pearlDiameter;
}

void Bracelet::accept(VisitorInterface& visitor) {
    visitor.visitBracelet(*this);
}

void Models::Accessories::Bracelet::setPearlNumber(unsigned int pearlNumber) {
    this->pearlNumber = pearlNumber;
}

void Models::Accessories::Bracelet::setPearlDiameter(double pearlDiameter) {
    this->pearlDiameter = pearlDiameter;
}
