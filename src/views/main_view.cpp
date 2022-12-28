

#include <QMessageBox>
#include "main_view.h"
#include "../services/connectivity_manager.h"
#include "no_connection.h"
#include "products_view.h"

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
        setWindowTitle("Connection Error");
        setCentralWidget(new NoConnection());
        return;
    }

    setWindowTitle("Clothing FaQTory");

    tabWidget = new QTabWidget;

    MainController* controller = new MainController(this);
    setController(controller);
    productsView = new ProductsView(this, tabWidget);
    materialsView = new MaterialsView(this, tabWidget);

    ProductsMap products = controller->findAllProductsByType();
    productsView->init(products);

    materialsView->init();

    connect(materialsView, SIGNAL(materialCostChanged()), productsView, SLOT(rebuildTreeView()));

    tabWidget->addTab(productsView, "Products");
    QIcon clothingIcon(":/assets/icons/tshirt.png");
    tabWidget->setTabIcon(0, clothingIcon);

    tabWidget->addTab(materialsView, "Materials Cost");
    QIcon materialsIcon(":/assets/icons/money.png");
    tabWidget->setTabIcon(1, materialsIcon);

    tabWidget->setIconSize(QSize(35, 35));

    setCentralWidget(tabWidget);
    setWindowIcon(clothingIcon);
}

void MainView::handleDatabaseError(Error* e) {

    QMessageBox* errorBox = new QMessageBox;
    errorBox->setWindowTitle(QString::fromStdString(e->getType()));
    errorBox->setText(QString::fromStdString(e->getUserMessage()));
    errorBox->setStandardButtons(QMessageBox::Abort);
    errorBox->setIcon(QMessageBox::Critical);
    errorBox->setDefaultButton(QMessageBox::Abort);
    errorBox->setAttribute(Qt::WA_DeleteOnClose);
    errorBox->resize(300, 200);
    errorBox->show();
    qFatal("Aborting due to database error.");

}