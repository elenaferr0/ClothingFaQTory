#include "overalls.h"

using Models::ClothingItems::Overalls;

Overalls::Overalls(int id,
                   const string& code,
                   const string& color,
                   const Material& material,
                   const Size& size,
                   int availableQuantity,
                   int soldQuantity,
                   const string& description,
                   bool sustainableMaterials,
                   const string& gender,
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

void Overalls::accept(VisitorInterface& visitor) {
    visitor.visitOveralls(*this);
}
