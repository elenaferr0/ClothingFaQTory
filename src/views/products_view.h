#ifndef PRODUCT_VIEW_H
#define PRODUCT_VIEW_H

#include "observer_widget_view.h"
#include "../models/product.h"
#include "../core/containers/map.h"
#include "../core/errors/error.h"
#include "wizard/create_product_wizard.h"
#include "view.h"
#include <memory>
#include <QToolBar>
#include <QTreeWidgetItem>
#include <QTreeWidget>

using std::shared_ptr;
using Models::Product;
using Core::Containers::Map;
using Core::Error;

namespace Views {
    class ProductsView : public ObserverWidgetView {
        Q_OBJECT
        private:
            typedef Map <Product::ProductType, list<shared_ptr < Product>>>
            ProductsMap;

            ProductsMap productsByType;

            static int COLUMN_COUNT;

            QTreeWidget* treeWidget;
            QToolBar* toolBar;

            QTreeWidgetItem* getHeaders();

            void initTreeView();

        public:
            ProductsView(QWidget* parent = nullptr);

            void init(const ProductsMap& productsByType);

            void notify(Model*) override;

        private slots:

            void showWizard(bool);
    };

}

#endif //PRODUCT_VIEW_H
