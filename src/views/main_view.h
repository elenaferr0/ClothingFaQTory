

#ifndef VIEW_H
#define VIEW_H


#include "../controllers/controller.h"
#include "../models/product.h"
#include <memory>
#include <QStackedWidget>
#include <QTabWidget>
#include <QMainWindow>
#include "products_view.h"

using std::shared_ptr;
using Views::ProductsView;

namespace Controllers {
    class Controller;
}

using Controllers::Controller;

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

    protected:
        Controller* controller;
        ProductsView* productsView;
    private:
        QTabWidget* tabWidget;
    };
}


#endif //VIEW_H
