

#ifndef VIEW_H
#define VIEW_H


#include "../controllers/main_controller.h"
#include "../models/product.h"
#include <memory>
#include <QStackedWidget>
#include <QTabWidget>
#include <QMainWindow>
#include "products_view.h"

using std::shared_ptr;
using Views::ProductsView;

namespace Controllers {
    class MainController;
}

using Controllers::MainController;

QT_BEGIN_NAMESPACE
namespace Views { class MainView; }
QT_END_NAMESPACE

namespace Views {
    class MainView : public QMainWindow {
    Q_OBJECT
        typedef Map<Product::ProductType, list<shared_ptr<Product>>> ProductsMap;

    public:
        MainView(QWidget* parent = nullptr);

        ProductsView* getProductsView() const;

    private:
        MainController* controller;
        ProductsView* productsView;
        QTabWidget* tabWidget;

    public slots:
        void handleDatabaseError(Error*);
    };
}


#endif //VIEW_H
