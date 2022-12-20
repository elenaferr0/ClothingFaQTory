

#include "main_view.h"
#include "../services/connectivity_manager.h"
#include "no_connection.h"
using Views::ProductsView;
using Views::NoConnection;

MainView::MainView(QWidget* parent) : QMainWindow(parent) {

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

    productsView = new ProductsView(tabWidget);
    this->controller = new MainController(this);

    ProductsMap products = controller->findAllProductsByType();
    productsView->init(products);


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

void Views::MainView::handleDatabaseError(Error* e) {
    qCritical() << e;
}
