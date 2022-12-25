#ifndef PRODUCT_VIEW_H
#define PRODUCT_VIEW_H

#include "observer_widget_view.h"
#include "../models/product.h"
#include "../core/containers/map.h"
#include "../core/errors/error.h"
#include "wizard/create_product_wizard_view.h"
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

            ProductsMap productsByType;

            static int COLUMN_COUNT;

            QTreeWidget* treeWidget;
            QToolBar* toolBar;

            QTreeWidgetItem* getHeaders() const;

            void initTreeView();

            QIcon drawColorIcon(const string& hex);

            static const int COLOR_ICON_SIZE = 20;

            void buildAndInsertChild(QTreeWidgetItem*, Product*, Product::ProductType);

        public:
            ProductsView(MainView* mainView, QWidget* parent = nullptr);

            void init(const ProductsMap& productsByType);

            void notify(Model*) override;

        public slots:

            void rebuildTreeView();

        private slots:

            void handleProductCreation(Product*, Product::ProductType);

            void showWizard(bool);

            void clickedEditButton(int, QTreeWidgetItem*, Product::ProductType);

            void clickedDeleteButton(int, QTreeWidgetItem*, Product::ProductType);

    };

}

#endif //PRODUCT_VIEW_H
