

#ifndef ICON_BUTTON_H
#define ICON_BUTTON_H

#include <QObject>
#include <QPushButton>
#include "../../models/product.h"

using Models::Product;

QT_BEGIN_NAMESPACE
namespace Views::Components { class IconButton; }
QT_END_NAMESPACE

class IconButton : public QPushButton {
    Q_OBJECT
    private:
        int id;
        QTreeWidgetItem* row;
        Product::ProductType productType;

    public:
        IconButton(const QString& path, const QString& objName, int id, QTreeWidgetItem* row, Product::ProductType,
                   QWidget* parent);

    private slots:

        void handleClick(bool);

    signals:

        void clicked(int, QTreeWidgetItem*, Product::ProductType);
};


#endif //ICON_BUTTON_H
