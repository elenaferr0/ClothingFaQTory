

#ifndef ICON_BUTTON_H
#define ICON_BUTTON_H

#include <QObject>
#include <QPushButton>
#include <QTreeWidgetItem>
#include "../../models/product.h"

using Models::Product;

QT_BEGIN_NAMESPACE
namespace Views::Components { class IconButton; }
QT_END_NAMESPACE

class ProductIconButton : public QPushButton {
    Q_OBJECT
    private:
        Product* product;
        QTreeWidgetItem* row;
        Product::ProductType productType;

    public:
        ProductIconButton(const QString& path,
                          const QString& objName,
                          Product* product,
                          QTreeWidgetItem* row,
                          Product::ProductType,
                          QWidget* parent);

    private slots:

        void handleClick(bool);

    signals:

        void clicked(Product*, QTreeWidgetItem*, Product::ProductType);
};


#endif //ICON_BUTTON_H
