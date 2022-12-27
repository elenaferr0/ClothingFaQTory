#ifndef OVERALLS_H
#define OVERALLS_H

#include "vest.h"
#include "jeans.h"

using Models::ClothingItems::Vest;
using Models::ClothingItems::Jeans;
using Models::Material;
using Models::Size;

namespace Models::ClothingItems {
    class Overalls : public Vest, public Jeans {
        public:
            Overalls(int id = -1,
                     const string& code = "",
                     const string& color = "",
                     const Material& material = Material(),
                     const Size& size = Size(),
                     int availableQuantity = 0,
                     int soldQuantity = 0,
                     const string& description = "",
                     bool sustainableMaterials = false,
                     const string& gender = "",
                     bool shorts = false,
                     bool hasButtons = false);

            double computePrice() const override;

            Overalls* clone() const override;

            void accept(VisitorInterface& visitor) override;
    };
}

#endif // OVERALLS_H
