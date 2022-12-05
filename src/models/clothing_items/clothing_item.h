#ifndef CLOTHINGITEM_H
#define CLOTHINGITEM_H

#include "src/models/product.h"

namespace Models {
    class ClothingItem : public Product {
    public:
        enum Gender {
            MEN, WOMEN, UNISEX
        };

        ClothingItem(unsigned long id = 0,
                     string code = "",
                     string color = "",
                     list <Material> materials = list<Material>(),
                     Size size = Size(),
                     int availableQuantity = 0,
                     int soldQuantity = 0,
                     string description = "",
                     bool sustainableMaterials = false,
                     Gender gender = Gender::UNISEX);

        string getTableName() const override;
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
