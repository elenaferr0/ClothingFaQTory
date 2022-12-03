#ifndef JEANS_H
#define JEANS_H

#include "src/models/clothing_items/clothingitem.h"
#include<list>

using std::list;

namespace Models::ClothingItems {
    class Jeans : public virtual ClothingItem {
    private:
        // if shorts is true, when calculating the price half the length will be used
        bool shorts;
    public:
        Jeans(unsigned long id,
              string code,
              string color,
              list <Material> materials,
              Size size,
              int availableQuantity,
              int soldQuantity,
              string description,
              bool sustainableMaterials = false,
              Gender gender = Gender::UNISEX,
	      bool shorts = false
        );

        double computePrice() const override;

        Jeans* clone() const override;
    };
}

#endif // JEANS_H
