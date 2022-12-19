

#include "view.h"

using Views::ProductsView;
using Views::View;

View::View() : controller(new Controller) {
    ProductsMap products = controller->findAllProductsByType();
    productsView = new ProductsView(products);
}

ProductsView* View::getProductsView() const {
    return productsView;
}
