#ifndef I_OBSERVER_H
#define I_OBSERVER_H

#include "../models/product.h"

using Models::Product;

namespace Core {
    class IProductObserver {
    public:
        virtual void notify(Product& product) = 0;

        virtual ~IProductObserver() = default;

    };
}
#endif //I_OBSERVER_H
