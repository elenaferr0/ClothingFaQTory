#ifndef ACCESSORY_H
#define ACCESSORY_H

#include "../product.h"
#include "../material.h"
#include "../size.h"

namespace Models {
    class Accessory : public Product {

    public:
        enum Category {
            BAGS, JEWELRY, HATS, GENERAL
        };

        Accessory(long id = -1,
                  string code = "",
                  string color = "",
                  list<Material> materials = list<Material>(),
                  Size size = Size(),
                  int availableQuantity = 0,
                  int soldQuantity = 0,
                  string description = "",
                  string category = "");

        string getTableName() const override;

        string getCategoryAsString() const;

        static Category categoryFromString(const string&);

    protected:
        Category category;
    public:
        Category getCategory() const;

        void setCategory(const string&);
    };
}
#endif // ACCESSORY_H
