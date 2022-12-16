#ifndef BACKPACK_H
#define BACKPACK_H

#include <string>
#include "accessory.h"
#include "../../core/visitor_interface.h"

using std::string;

namespace Models::Accessories {
    class BackPack : public Accessory {
    protected:
        /*
         * static constants used to estimate the backpack size
         * for price calculation
         * assumption: all backpacks have same height and width,
         * only capacity changes
         */
        static const double BACKPACK_HEIGHT; // in cm
        static const double BACKPACK_WIDTH;  // in cm

        double capacity; // in liters
    public:
        BackPack(long id = -1,
                 string code = "",
                 string color = "",
                 Material material = Material(),
                 Size size = Size(),
                 int availableQuantity = 0,
                 int soldQuantity = 0,
                 string description = "",
                 string category = "",
                 double capacity = 0);

        BackPack* clone() const override;

        double computePrice() const override;

        const double& getCapacity() const;

        void accept(VisitorInterface& visitor) override;
    };
}

#endif // BACKPACK_H
