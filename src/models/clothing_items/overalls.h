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
            Overalls(long id = -1,
                     string code = "",
                     string color = "",
                     Material material = Material(),
                     Size size = Size(),
                     int availableQuantity = 0,
                     int soldQuantity = 0,
                     string description = "",
                     bool sustainableMaterials = false,
                     string gender = "",
                     bool shorts = false,
                     bool hasButtons = false);

            double computePrice() const override;

            Overalls* clone() const override;

            void accept(ModelVisitorInterface& visitor) override;
    };
}

#endif // OVERALLS_H
