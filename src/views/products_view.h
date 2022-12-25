#ifndef PRODUCT_VIEW_H
#define PRODUCT_VIEW_H

#include "observer_widget_view.h"
#include "../models/product.h"
#include "../core/containers/map.h"
#include "../core/errors/error.h"
#include "wizard/product_wizard_view.h"
#include "view.h"
#include "main_view.h"
#include <QToolBar>
#include <QTreeWidgetItem>
#include <QTreeWidget>

using Models::Product;
using Core::Containers::Map;
using Core::Error;

namespace Views {
    class MainView;

    class ProductsView : public ObserverWidgetView {
        Q_OBJECT
        private:
            typedef Map<Product::ProductType, LinkedList<Product*>>
                    ProductsMap;

            static int COLUMN_COUNT;

            QTreeWidget* treeWidget;
            QToolBar* toolBar;

            QTreeWidgetItem* getHeaders() const;

            void initTreeView(const ProductsMap& productsByType);

            QIcon drawColorIcon(const string& hex);

            static const int COLOR_ICON_SIZE = 20;

            void buildAndInsertChild(QTreeWidgetItem*, Product*, Product::ProductType);

            QList<QString> materials;
            QList<QString> sizes;
        public:
            ProductsView(MainView* mainView, QWidget* parent = nullptr);

            void init(const ProductsMap& productsByType);

            void notify(Model*) override;

        public slots:

            void rebuildTreeView();

        private slots:

            void handleProductCreation(Product*, Product::ProductType);

            void handleProductEditing(Product*, Product::ProductType);

            void showCreateProductWizard(bool);

            void clickedEditButton(Product*, QTreeWidgetItem*, Product::ProductType);

            void clickedDeleteButton(Product*, QTreeWidgetItem*, Product::ProductType);

    };

}

#endif //PRODUCT_VIEW_H
