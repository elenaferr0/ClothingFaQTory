#ifndef Vest_H
#define Vest_H

#include "src/models/clothing_items/clothingitem.h"

namespace Models::ClothingItems {
    class Vest : public virtual ClothingItem {
    private:
        bool hasButtons;
    public:
        Vest(unsigned long id,
             string code,
             string color,
             list <Material> materials,
             Size size,
             int availableQuantity,
             int soldQuantity,
             string description,
             bool sustainableMaterials = false,
	     Gender gender = Gender::UNISEX,
             bool hasButtons = false);

        double computePrice() const override;

        string getTableName() const override;

        Vest* clone() const override;
    };

}
#endif // Vest_H
