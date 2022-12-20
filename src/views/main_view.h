

#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H


#include "../controllers/main_controller.h"
#include "../models/product.h"
#include <memory>
#include <QStackedWidget>
#include <QTabWidget>
#include <QMainWindow>
#include "products_view.h"
#include "materials_view.h"
#include "view.h"

using std::shared_ptr;
using Views::ProductsView;
using Views::MaterialsView;


namespace Views {
    class MainView : public QMainWindow, public View {
        Q_OBJECT
            typedef Map<Product::ProductType, list<shared_ptr<Product>>> ProductsMap;
            typedef list<shared_ptr<Material>> MaterialsList;

        public:
            MainView(QWidget* parent = nullptr);

            ProductsView* getProductsView() const;

        private:
            ProductsView* productsView;
            MaterialsView* materialsView;
            QTabWidget* tabWidget;
        public slots:

            void handleDatabaseError(Error*);

        signals:

            void retryFetchingDataFromDB();
    };
}


#endif //MAIN_VIEW_H
