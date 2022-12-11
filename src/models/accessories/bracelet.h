#ifndef BRACELET_H
#define BRACELET_H

#include "accessory.h"

namespace Models::Accessories {
    class Bracelet : public Accessory {
    protected:
        unsigned int pearlNumber;
    public:
        unsigned int getPearlNumber() const;

        void setPearlNumber(unsigned int pearlNumber);

        double getPearlDiameter() const;

        void setPearlDiameter(double pearlDiameter);

    protected:
        double pearlDiameter;

    public:
        Bracelet(
                long id = -1,
                string code = "",
                string color = "",
                Material material = Material(),
                Size size = Size(),
                int availableQuantity = 0,
                int soldQuantity = 0,
                string description = "",
                string category = "",
                unsigned int pearlNumber = 0,
                double pearlDiameter = 0.75);

        Bracelet* clone() const override;



        double computePrice() const override;
    };
}

#endif // BRACELET_H
