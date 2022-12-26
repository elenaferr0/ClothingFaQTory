#ifndef ACCESSORY_H
#define ACCESSORY_H

#include "../product.h"
#include "../material.h"
#include "../size.h"

namespace Models {
    class Accessory : public Product {

        public:
            enum Category {
                GENERAL, BAGS, JEWELRY, HATS
            };

            Accessory(long id = -1,
                      string code = "",
                      string color = "",
                      Material material = Material(),
                      Size size = Size(),
                      int availableQuantity = 0,
                      int soldQuantity = 0,
                      string description = "",
                      string category = "");


            static string getCategoryAsString(Category);

            static Category categoryFromString(const string&);

        protected:
            Category category;
        public:
            const Category& getCategory() const;

            void setCategory(const string&);
    };
}
#endif // ACCESSORY_H
