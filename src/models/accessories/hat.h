#ifndef CAP_H
#define CAP_H

#include "accessory.h"

namespace Models::Accessories {
class Hat : public Accessory{
    private:
        bool isBaseballHat;
    public:
        Hat(unsigned long id = 0,
            string code = "",
            string color = "",
            list <Material> materials = list<Material>(),
            Size size = Size(),
            int availableQuantity = 0,
            int soldQuantity = 0,
            string description = "",
            Category category = Category::GENERAL,
            bool isBaseballHat = false);
        Hat* clone() const override;
        double computePrice() const override;
    };
}


#endif //CAP_H
