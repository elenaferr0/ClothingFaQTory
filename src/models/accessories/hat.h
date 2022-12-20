#ifndef CAP_H
#define CAP_H

#include "accessory.h"

namespace Models::Accessories {
    class Hat : public Accessory {
        private:
            bool baseballCap;
            static const double DIAMETER;
            static const double VISOR_LENGTH;
            static const double VISOR_WIDTH;
        public:
            Hat(long id = -1,
                string code = "",
                string color = "",
                Material material = Material(),
                Size size = Size(),
                int availableQuantity = 0,
                int soldQuantity = 0,
                string description = "",
                string category = "",
                bool isBaseballCap = false);

            Hat* clone() const override;

            double computePrice() const override;

            const bool& isBaseballCap() const;

            void accept(ModelVisitorInterface& visitor) override;
    };
}


#endif //CAP_H
