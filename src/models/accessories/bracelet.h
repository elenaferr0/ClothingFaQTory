#ifndef BRACELET_H
#define BRACELET_H

#include "src/models/accessories/accessory.h"

namespace Models::Accessories {
    class Bracelet : public Accessory {
    protected:
        unsigned int pearlNumber;
        double pearlDiameter;

    public:
        Bracelet(
                unsigned long id = 0,
                string code = "",
                string color = "",
                list <Material> materials = list<Material>(),
                Size size = Size(),
                int availableQuantity = 0,
                int soldQuantity = 0,
                string description = "",
                unsigned int pearlNumber = 0,
                double pearlDiameter = 0.75);

        Bracelet* clone() const override;

        double computePrice() const override;
    };
}

#endif // BRACELET_H
