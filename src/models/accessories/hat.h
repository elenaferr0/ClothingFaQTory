#ifndef CAP_H
#define CAP_H

#include "accessory.h"

namespace Models::Accessories {
    class Hat : public Accessory {
    private:
        bool isBaseballCap;
        static const unsigned double DIAMETER = 15.5;
        static const unsigned double VISOR_LENGTH = 10.25;
        static const unsigned double VISOR_WIDTH = 5.25;
    public:
        Hat(long id = -1,
            string code = "",
            string color = "",
            list <Material> materials = list<Material>(),
            Size size = Size(),
            int availableQuantity = 0,
            int soldQuantity = 0,
            string description = "",
            Category category = Category::GENERAL,
            bool isBaseballCap = false);

        Hat* clone() const override;

        double computePrice() const override;

        string getTableName() const override;

    };
}


#endif //CAP_H
