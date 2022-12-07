#ifndef JEANS_H
#define JEANS_H

#include "src/models/clothing_items/clothing_item.h"
#include<list>

using std::list;

namespace Models::ClothingItems {
    class Jeans : public virtual ClothingItem {
    private:
        // if shorts is true, when calculating the price half the length will be used
        bool shorts;
    public:
	Jeans(long id = -1,
	      string code = "",
	      string color = "",
	      list <Material> materials = list<Material>(),
	      Size size = Size(),
	      int availableQuantity = 0,
	      int soldQuantity = 0,
	      string description = "",
              bool sustainableMaterials = false,
              Gender gender = Gender::UNISEX,
	      bool shorts = false
        );

        double computePrice() const override;

        string getTableName() const override;

        Jeans* clone() const override;
    };
}

#endif // JEANS_H
