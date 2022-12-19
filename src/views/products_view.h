#ifndef PRODUCT_VIEW_H
#define PRODUCT_VIEW_H

#include "view_interface.h"
#include "../models/product.h"
#include "../core/containers/map.h"

using Models::Product;
using Core::Containers::Map;

namespace Views {
    class ProductsView : public ViewInterface {
    private:
        Map<Product::ProductType, Product*> productsByType;
    public:
        ProductsView(QWidget* parent = nullptr);

        void init() override;
    };

}

#endif //PRODUCT_VIEW_H
