#ifndef I_PRODUCT_OBSERVER_H
#define I_PRODUCT_OBSERVER_H

namespace Models {
    class Product;
}

using Models::Product;

namespace Core {
    class IProductObserver {
    public:
        virtual void notify(Product& product) = 0;

        virtual ~IProductObserver() = default;

    };
}
#endif //IPRODUCT_OBSERVER_H
