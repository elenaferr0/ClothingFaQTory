#ifndef BRACELET_H
#define BRACELET_H

#include "../../core/visitors/model_visitor_interface.h"

#include "accessory.h"

using Core::Visitors::ModelVisitorInterface;

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

            void accept(ModelVisitorInterface& visitor) override;
    };
}

#endif // BRACELET_H
