

#include "main_view.h"
#include "../services/connectivity_manager.h"
#include "no_connection.h"

using Views::ProductsView;
using Views::NoConnection;
using Views::MainView;
using Controllers::MainController;

MainView::MainView(QWidget* parent) : QMainWindow(parent) {

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

    db.setDatabaseName("clothingfaqtory");
    db.setHostName("129.152.21.9");
    db.setPort(5432);
    db.setUserName("qtuser");
    db.setPassword("8rF6*%3t8uQV1jYV6U0m");

    if (!ConnectivityManager::checkConnection() || !db.open()) {
        QMainWindow::setWindowTitle("Connection Error");
        setCentralWidget(new NoConnection());
        return;
    }

    QMainWindow::setWindowTitle("Clothing FaQTory");

    tabWidget = new QTabWidget;

    productsView = new ProductsView(tabWidget);
    materialsView = new MaterialsView(tabWidget);
    this->controller = new MainController(this);

    MainController* controller = new MainController(this);
    setController(controller);

    ProductsMap products = controller->findAllProductsByType();
    productsView->init(products);

    MaterialsList materials = controller->findAllMaterials();
    materialsView->init(materials);

    tabWidget->addTab(productsView, "Products");
    QIcon clothingIcon(":/assets/icons/tshirt.png");
    tabWidget->setTabIcon(0, clothingIcon);

    tabWidget->addTab(materialsView, "Materials Cost");
    QIcon materialsIcon(":/assets/icons/materials_cost.png");
    tabWidget->setTabIcon(1, materialsIcon);

    tabWidget->setIconSize(QSize(35, 35));

    setCentralWidget(tabWidget);
}

ProductsView* MainView::getProductsView() const {
    return productsView;
}

void MainView::handleDatabaseError(Error* e) {
    qCritical() << e;
}