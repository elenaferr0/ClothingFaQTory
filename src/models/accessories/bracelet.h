#ifndef BRACELET_H
#define BRACELET_H

#include "accessory.h"

namespace Models::Accessories {
    class Bracelet : public Accessory {
    protected:
        unsigned int pearlNumber;
        double pearlDiameter;

    public:
        Bracelet(
                long id = -1,
                string code = "",
                string color = "",
                list<Material> materials = list<Material>(),
                Size size = Size(),
                int availableQuantity = 0,
                int soldQuantity = 0,
                string description = "",
                string category = "",
                unsigned int pearlNumber = 0,
                double pearlDiameter = 0.75);

        Bracelet* clone() const override;

        string getTableName() const override;

        double computePrice() const override;
    };
}

#endif // BRACELET_H
