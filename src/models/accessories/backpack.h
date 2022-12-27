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
            BackPack(int id = -1,
                     const string& code = "",
                     const string& color = "",
                     const Material& material = Material(),
                     const Size& size = Size(),
                     int availableQuantity = 0,
                     int soldQuantity = 0,
                     const string& description = "",
                     const string& category = "",
                     double capacity = 0);

            BackPack* clone() const override;

            double computePrice() const override;

            const double& getCapacity() const;

            void setCapacity(double capacity);

            void accept(VisitorInterface& visitor) override;
    };
}

#endif // BACKPACK_H
