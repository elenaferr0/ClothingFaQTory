#include <memory>
#include "product_factory.h"

using std::make_shared;
using std::static_pointer_cast;

shared_ptr <Product> ProductFactory::createProduct(Product::ProductType productType) {
    shared_ptr<Product> product(nullptr);
    switch (productType) {
        case Product::Jeans: {
            shared_ptr<Jeans> jeans = make_shared<Jeans>();
            product = static_pointer_cast<Product>(jeans);
            break;
        }
        case Product::Overalls: {
            shared_ptr<Overalls> overalls = make_shared<Overalls>();
            product = static_pointer_cast<Product>(overalls);
            break;
        }
        case Product::Hat: {
            shared_ptr<Hat> hat = make_shared<Hat>();
            product = static_pointer_cast<Product>(hat);
            break;
        }
        case Product::Bracelet: {
            shared_ptr<Bracelet> bracelet = make_shared<Bracelet>();
            product = static_pointer_cast<Product>(bracelet);
            break;
        }
        case Product::Vest: {
            shared_ptr<Vest> vest = make_shared<Vest>();
            product = static_pointer_cast<Product>(vest);
            break;
        }
        case Product::BackPack: {
            shared_ptr<BackPack> backpack = make_shared<BackPack>();
            product = static_pointer_cast<Product>(backpack);
            break;
        }
    }
    return product;
}
