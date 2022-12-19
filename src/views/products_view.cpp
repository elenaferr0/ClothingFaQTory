

#include "products_view.h"

using Views::ProductsView;

ProductsView::ProductsView(ProductsMap& productsByType, QWidget* parent) :
        productsByType(productsByType), ViewInterface(parent) {}

void ProductsView::init() {

}

void Views::ProductsView::notify(Product& product) {
    // update tree widget of the given product
}


