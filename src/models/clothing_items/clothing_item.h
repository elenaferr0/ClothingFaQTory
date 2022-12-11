#ifndef CLOTHINGITEM_H
#define CLOTHINGITEM_H

#include "../product.h"
#include "../material.h"

namespace Models {
    class ClothingItem : public Product {
    public:
        enum Gender {
            MEN, WOMEN, UNISEX
        };

        ClothingItem(long id = -1,
                     string code = "",
                     string color = "",
                     Material material = Material(),
                     Size size = Size(),
                     int availableQuantity = 0,
                     int soldQuantity = 0,
                     string description = "",
                     bool sustainableMaterials = false,
                     string gender = "");



        string getGenderAsString() const;
        Gender genderFromString(const string&) const;

        ClothingItem& operator=(const ClothingItem&) = default; // needed because it's a virtual base

        bool hasSustainableMaterials() const;

        void setSustainableMaterials(bool sustainableMaterials);

    protected:
        double computeLegLength() const;

        double computeTrunkLength() const;

        double computeLegWidth() const;

        double computeTrunkWidth() const;

        bool sustainableMaterials;
        Gender gender;

        // constants used for top part clothing
        static const double SMALLEST_SIZE_TRUNK_WIDTH;
        static const double SMALLEST_SIZE_TRUNK_LENGTH;

        // constants used for bottom part clothing
        static const double SMALLEST_SIZE_LEG_WIDTH;
        static const double SMALLEST_SIZE_LEG_LENGTH;


    };
}

#endif // CLOTHINGITEM_H
