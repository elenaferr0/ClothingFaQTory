#include "bracelet.h"
#include "../../utils/calculator.h"

using Models::Material;
using Models::Accessories::Bracelet;
using Utils::Calculator;

Bracelet::Bracelet(
        long id,
        string code,
        string color,
        list <Material> materials,
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
                    materials,
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
    Material material = materials.front();

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

    double totalWeight = specificWeight * (pearlVolume * pearlNumber);

    return totalWeight * material.getCostPerUnit();
}

string Bracelet::getTableName() const {
    return "bracelet";
}
