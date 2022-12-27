#ifndef BRACELET_H
#define BRACELET_H

#include "../../core/visitor_interface.h"

#include "accessory.h"

using Core::VisitorInterface;

namespace Models::Accessories {
    class Bracelet : public Accessory {
        protected:
            unsigned int pearlNumber;
        public:
            const unsigned int& getPearlNumber() const;

            const double& getPearlDiameter() const;

        protected:
            double pearlDiameter;

        public:
            Bracelet(
                    int id = -1,
                    const string& code = "",
                    const string& color = "",
                    const Material& material = Material(),
                    const Size& size = Size(),
                    int availableQuantity = 0,
                    int soldQuantity = 0,
                    const string& description = "",
                    const string& category = "",
                    unsigned int pearlNumber = 0,
                    double pearlDiameter = 0.75);

            double computePrice() const override;

            void setPearlNumber(unsigned int pearlNumber);

            void setPearlDiameter(double pearlDiameter);

            void accept(VisitorInterface& visitor) override;
    };
}

#endif // BRACELET_H
