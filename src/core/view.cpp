

#include "view.h"
#include "../views/products_view.h"

using Views::ProductsView;
using Core::View;


View::View() : controller(new Controller) {
    Map < Product::ProductType, list<shared_ptr < Product>>> products = controller->findAllProductsByType();
    productsView = new ProductsView(nullptr, products);
}
