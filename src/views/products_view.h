#ifndef PRODUCT_VIEW_H
#define PRODUCT_VIEW_H

#include "widget_view_parent.h"
#include "../models/product.h"
#include "../core/containers/map.h"
#include "../core/errors/error.h"
#include "wizard/product_wizard_view.h"
#include "view.h"
#include "filter_dialog.h"
#include "main_view.h"
#include "components/empty_state.h"
#include "info_dialog_visitor.h"
#include <QToolBar>
#include <QToolButton>
#include <QStackedWidget>
#include <QTreeWidgetItem>
#include <QTreeWidget>

using Models::Product;
using Core::Containers::Map;
using Core::Error;

namespace Views {
    class MainView;

    class FilterDialog;

    class ProductsView : public WidgetViewParent {
        Q_OBJECT
        private:
            typedef Map<Product::ProductType, LinkedList<shared_ptr<Product>>>
                    ProductsMap;

            static const unsigned int COLUMN_COUNT = 10;
            static const unsigned int EMPTY_STATE_IDX = 0;
            static const unsigned int TREE_VIEW_IDX = 1;
            QList<QString> materials;
            QList<QString> sizes;
            QToolButton* clearFiltersButton;
            QPair<double, double> priceRangeFilter;
            QTreeWidget* treeWidget;
            QToolButton* filterButton;
            QToolButton* exportButton;
            QToolBar* toolBar;
            MainView* mainView;
            QStackedWidget* stack;

            QTreeWidgetItem* getHeaders() const;

            void initTreeView(const ProductsMap& productsByType);

            void buildAndInsertChild(QTreeWidgetItem*, shared_ptr<Product>, Product::ProductType);

            QStringList getColumnsFromProduct(const shared_ptr<Product> product) const;



        public:
            ProductsView(MainView* mainView, QWidget* parent = nullptr);

            void init(const ProductsMap& productsByType);

        public slots:

            void rebuildTreeView();

        private slots:

            void handleProductCreation(shared_ptr<Product>, Product::ProductType);

            void handleProductEditing(shared_ptr<Product>, Product::ProductType);

            void showCreateProductWizard();

            void clickedEditButton(shared_ptr<Product>, QTreeWidgetItem* row, Product::ProductType);

            void clickedDeleteButton(shared_ptr<Product>, QTreeWidgetItem* row, Product::ProductType);

            void clickedInfoButton(shared_ptr<Product>, QTreeWidgetItem* row, Product::ProductType);

            void handleExportJsonButtonClicked();

            void handleClearFilterButtonClicked();

            void handleFilterButtonClicked();

            void handleFilterDialogCompleted(Filters filters);

    };

}

#endif //PRODUCT_VIEW_H
