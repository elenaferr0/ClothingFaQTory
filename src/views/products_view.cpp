

#include "products_view.h"

using Views::ProductsView;

Views::ProductsView::ProductsView(QWidget* parent) : ViewInterface(parent),
                                                     productsByType(Map<Product::ProductType, Product*>()) {}

void ProductsView::init() {

}


