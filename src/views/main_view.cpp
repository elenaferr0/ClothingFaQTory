

#include "main_view.h"
#include "../services/connectivity_manager.h"
#include "no_connection.h"
#include "../views/no_connection.h"

using Views::ProductsView;
using Views::MainView;
using Views::NoConnection;

MainView::MainView(QWidget* parent) : QMainWindow(parent), controller(new Controller) {
    ProductsMap products = controller->findAllProductsByType();
    productsView = new ProductsView(products, tabWidget);

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

    db.setDatabaseName("clothingfaqtory");
    db.setHostName("129.152.21.9");
    db.setPort(5432);
    db.setUserName("qtuser");
    db.setPassword("8rF6*%3t8uQV1jYV6U0m");

    if (!ConnectivityManager::checkConnection() || !db.open()) {
        setWindowTitle("Connection Error");
        setCentralWidget(new NoConnection());
        return;
    }

    setWindowTitle("Clothing FaQTory");

    tabWidget = new QTabWidget;

    tabWidget->addTab(productsView, "Products");
    QIcon clothingIcon(":/assets/icons/tshirt.png");
    tabWidget->setTabIcon(0, clothingIcon);

//    tabWidget->addTab(new MaterialsCostTabPage(tabWidget), "Materials Cost");
//    QIcon materialsIcon(":/assets/icons/materials_cost.png");
//    tabWidget->setTabIcon(1, materialsIcon);

    tabWidget->setIconSize(QSize(35, 35));

    setCentralWidget(tabWidget);
}

ProductsView* MainView::getProductsView() const {
    return productsView;
}
