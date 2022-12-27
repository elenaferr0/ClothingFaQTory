#ifndef CLOTHINGITEM_H
#define CLOTHINGITEM_H

#include "../product.h"
#include "../material.h"

namespace Models {
    class ClothingItem : public Product {
        public:
            enum Gender {
                UNISEX, MEN, WOMEN
            };

            ClothingItem(int id = -1,
                         const string& code = "",
                         const string& color = "",
                         const Material& material = Material(),
                         const Size& size = Size(),
                         int availableQuantity = 0,
                         int soldQuantity = 0,
                         const string& description = "",
                         bool sustainableMaterials = false,
                         const string& gender = "");


            static string getGenderAsString(Gender);

            static Gender genderFromString(const string&);

            ClothingItem& operator=(const ClothingItem&) = default; // needed because it's a virtual base

            const bool& hasSustainableMaterials() const;

            void setSustainableMaterials(bool sustainableMaterials);

            Gender getGender() const;

            void setGender(Gender gender);

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
