#ifndef ACCESSORY_H
#define ACCESSORY_H

#include "src/models/product.h"

namespace Models {
    class Accessory : public Product {

    public:
        enum Category {
            BAGS, JEWELRY, HATS, GENERAL
        };

	Accessory(long id = -1,
                  string code = "",
                  string color = "",
                  list <Material> materials = list<Material>(),
                  Size size = Size(),
                  int availableQuantity = 0,
                  int soldQuantity = 0,
                  string description = "",
                  Category category = Category::GENERAL);

        string getTableName() const override;

    protected:
        Category category;
    };
}
#endif // ACCESSORY_H
