#ifndef JEANS_H
#define JEANS_H

#include "clothing_item.h"
#include "../material.h"
#include "../size.h"
#include<list>
#include<string>

using std::list;
using std::string;

namespace Models::ClothingItems {
    class Jeans : public virtual ClothingItem {
        private:
            // if shorts is true, when calculating the price half the length will be used
            bool shorts;
        public:
            const bool& areShorts() const;

            void setShorts(bool shorts);

        public:
            Jeans(long id = -1,
                  string code = "",
                  string color = "",
                  Material material = Material(),
                  Size size = Size(),
                  int availableQuantity = 0,
                  int soldQuantity = 0,
                  string description = "",
                  bool sustainableMaterials = false,
                  string gender = "",
                  bool shorts = false
            );

            double computePrice() const override;

            Jeans* clone() const override;

            void accept(VisitorInterface& visitor) override;
    };
}

#endif // JEANS_H
