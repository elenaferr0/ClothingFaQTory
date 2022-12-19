

#include "product_view.h"

using Views::ProductView;

Views::ProductView::ProductView(QWidget* parent) : ViewInterface(parent),
                                                   productsByType(Map<Product::ProductType, Product*>()) {}

void ProductView::init() {

}


