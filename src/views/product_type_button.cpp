

#include "product_type_button.h"

ProductTypeButton::ProductTypeButton(QWidget* parent, int productType) : QPushButton(parent), productType(productType) {
    connect(this, SIGNAL(clicked(bool)), this, SLOT(handleClick(bool)));
}

void ProductTypeButton::handleClick(bool) {
    emit clicked(productType);
}
