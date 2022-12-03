#include "overalls.h"

using Models::ClothingItems::Overalls;

Overalls::Overalls(unsigned long id,
                   string code,
                   string color,
                   list <Material> materials,
                   Size size,
                   int availableQuantity,
                   int soldQuantity,
                   string description,
                   bool sustainableMaterials,
                   Gender gender,
                   bool shorts,
                   bool hasButtons)
        : Vest(id,
               code,
               color,
               materials,
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
                materials,
                size,
                availableQuantity,
                soldQuantity,
                description,
                sustainableMaterials,
                gender,
		shorts){};

Overalls* Overalls::clone() const {
    return new Overalls(*this);
}

double Overalls::computePrice() const {
    return Jeans::computePrice() + Vest::computePrice();
}
