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
            Hat(int id = -1,
                const string& code = "",
                const string& color = "",
                const Material& material = Material(),
                const Size& size = Size(),
                int availableQuantity = 0,
                int soldQuantity = 0,
                const string& description = "",
                const string& category = "",
                bool isBaseballCap = false);

            double computePrice() const override;

            const bool& isBaseballCap() const;

            void accept(VisitorInterface& visitor) override;

            void setBaseballCap(bool baseballCap);
    };
}


#endif //CAP_H
