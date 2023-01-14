#ifndef PRODUCTFACTORY_H
#define PRODUCTFACTORY_H

#include <string>
#include "../models/product.h"
#include "../models/clothing_items/jeans.h"
#include "../models/clothing_items/vest.h"
#include "../models/clothing_items/overalls.h"
#include "../models/accessories/backpack.h"
#include "../models/accessories/bracelet.h"
#include "../models/accessories/hat.h"
#include "../models/product.h"

using std::string;
using Models::Product;
using Models::ClothingItems::Jeans;
using Models::ClothingItems::Vest;
using Models::ClothingItems::Overalls;
using Models::Accessories::BackPack;
using Models::Accessories::Bracelet;
using Models::Accessories::Hat;
using std::shared_ptr;

class ProductFactory {
public:
    shared_ptr<Product> createProduct(Product::ProductType productType);
};

#endif //PRODUCTFACTORY_H
