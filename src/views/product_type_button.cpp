

#include "product_type_button.h"

ProductTypeButton::ProductTypeButton(int productType, QWidget* parent) : productType(productType), QPushButton(parent) {
    connect(this, SIGNAL(clicked(bool)), this, SLOT(handleClick(bool)));
}

void ProductTypeButton::handleClick(bool) {
    emit clicked(productType);
}
