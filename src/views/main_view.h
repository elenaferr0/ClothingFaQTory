

#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H


#include "../controllers/main_controller.h"
#include "../models/product.h"
#include <QStackedWidget>
#include <QTabWidget>
#include <QMainWindow>
#include "products_view.h"
#include "materials_view.h"
#include "view.h"

namespace Views {
    class ProductsView;

    class MaterialsView;
}
using Views::ProductsView;
using Views::MaterialsView;


namespace Views {
    class MainView : public QMainWindow, public View {
        Q_OBJECT
            typedef Map<Product::ProductType, LinkedList<Product*>> ProductsMap;

        public:
            MainView(QWidget* parent = nullptr);

            ProductsView* getProductsView() const;

        private:
            ProductsView* productsView;
            MaterialsView* materialsView;
            QTabWidget* tabWidget;
        public slots:

            void handleDatabaseError(Error*);

    };
}


#endif //MAIN_VIEW_H
