#ifndef OVERALLS_H
#define OVERALLS_H

#include "vest.h"
#include "jeans.h"

namespace Models::ClothingItems {
    class Overalls : public Vest, public Jeans {
    public:
        Overalls(long id = -1,
                 string code = "",
                 string color = "",
                 list <Material> materials = list<Material>(),
                 Size size = Size(),
                 int availableQuantity = 0,
                 int soldQuantity = 0,
                 string description = "",
                 bool sustainableMaterials = false,
                 Gender gender = Gender::UNISEX,
                 bool shorts = false,
                 bool hasButtons = false);

        double computePrice() const override;

        string getTableName() const override;

        Overalls* clone() const override;
    };
}

#endif // OVERALLS_H
