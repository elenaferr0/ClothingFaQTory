#ifndef PRODUCT_VIEW_H
#define PRODUCT_VIEW_H

#include "widget_view_parent.h"
#include "../models/product.h"
#include "../core/containers/map.h"
#include "../core/errors/error.h"
#include "wizard/product_wizard_view.h"
#include "view.h"
#include "search_dialog.h"
#include "main_view.h"
#include <QToolBar>
#include <QTreeWidgetItem>
#include <QTreeWidget>

using Models::Product;
using Core::Containers::Map;
using Core::Error;

namespace Views {
    class MainView;

    class SearchDialog;

    class ProductsView : public WidgetViewParent {
        Q_OBJECT
        private:
            typedef Map<Product::ProductType, LinkedList<Product*>>
                    ProductsMap;

            static const int COLUMN_COUNT;

            QTreeWidget* treeWidget;
            QToolBar* toolBar;

            QTreeWidgetItem* getHeaders() const;

            void initTreeView(const ProductsMap& productsByType);

            QIcon drawColorIcon(const string& hex);

            static const int COLOR_ICON_SIZE = 20;

            void buildAndInsertChild(QTreeWidgetItem*, Product*, Product::ProductType);

            QStringList getColumnsFromProduct(const Product* product) const;

            QList<QString> materials;
            QList<QString> sizes;
            SearchDialog* searchDialog;
            QToolButton* clearFiltersButton;

            QPair<double, double> priceRangeFilter;

        public:
            ProductsView(MainView* mainView, QWidget* parent = nullptr);

            void init(const ProductsMap& productsByType);

        public slots:

            void rebuildTreeView();

        private slots:

            void handleProductCreation(Product*, Product::ProductType);

            void handleProductEditing(Product*, Product::ProductType);

            void showCreateProductWizard();

            void clickedEditButton(Product*, QTreeWidgetItem* row, Product::ProductType);

            void clickedDeleteButton(Product*, QTreeWidgetItem* row, Product::ProductType);

            void handleExportJsonButtonClicked();

            void handleClearFilterButtonClicked();

            void handleSearchButtonClicked();

            void handleSearchDialogCompleted(Filters filters);

    };

}

#endif //PRODUCT_VIEW_H
