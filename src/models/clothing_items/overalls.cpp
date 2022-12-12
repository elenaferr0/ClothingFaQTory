#include "overalls.h"

using Models::ClothingItems::Overalls;

Overalls::Overalls(long id,
                   string code,
                   string color,
                   Material material,
                   Size size,
                   int availableQuantity,
                   int soldQuantity,
                   string description,
                   bool sustainableMaterials,
                   string gender,
                   bool shorts,
                   bool hasButtons)
        : Vest(id,
               code,
               color,
               material,
               size,
               availableQuantity,
               soldQuantity,
               description,
               sustainableMaterials,
               gender,
               hasButtons),
          Jeans(id,
                code,
                color,
                material,
                size,
                availableQuantity,
                soldQuantity,
                description,
                sustainableMaterials,
                gender,
                shorts) {};

Overalls* Overalls::clone() const {
    return new Overalls(*this);
}

double Overalls::computePrice() const {
    return Jeans::computePrice() + Vest::computePrice();
}

void Overalls::accept(IProductVisitor& visitor) {
    visitor.visitOveralls(*this);
}
