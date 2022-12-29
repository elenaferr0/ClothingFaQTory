
#include <QTreeWidgetItem>
#include "product_icon_button.h"

ProductIconButton::ProductIconButton(Product* product,
                                     QTreeWidgetItem* row,
                                     Product::ProductType productType,
                                     QWidget* parent)
        : QPushButton(parent), product(product), row(row), productType(productType) {
    connect(this, SIGNAL(clicked(bool)), this, SLOT(handleClick(bool)));

    setIconSize(QSize(25, 25));
}

void ProductIconButton::handleClick(bool) {
    emit clicked(product, row, productType);
}

