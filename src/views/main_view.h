

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
#include "../services/connection/connectivity_manager.h"

namespace Views {
    class ProductsView;

    class MaterialsView;

    class FilterDialog;
}
using Views::ProductsView;
using Views::MaterialsView;
using Views::FilterDialog;


namespace Views {
    class MainView : public QMainWindow, public View {
        Q_OBJECT
            typedef Map<Product::ProductType, LinkedList<shared_ptr<Product>>> ProductsMap;

        public:
            MainView(QWidget* parent = nullptr);

            ~MainView();

        private:
            ProductsView* productsView;
            MaterialsView* materialsView;
            QTabWidget* tabWidget;
            ConnectivityManager* connectivityManager;

        public slots:

            void handleDatabaseError(Error*);

    };
}


#endif //MAIN_VIEW_H
