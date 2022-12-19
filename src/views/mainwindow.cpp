#include "mainwindow.h"
#include<iostream>
#include <QSqlDatabase>
#include <QBoxLayout>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include "no_connection.h"
#include "tabs/products/products_tab_page.h"
#include "tabs/materials_cost/materials_cost_tab_page.h"
#include "../services/connectivity_manager.h"

MainWindow::MainWindow(QWidget* parent)
        : QMainWindow(parent) {

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

    db.setDatabaseName("clothingfaqtory");
    db.setHostName("129.152.21.9");
    db.setPort(5432);
    db.setUserName("qtuser");
    db.setPassword("8rF6*%3t8uQV1jYV6U0m");

    if (!ConnectivityManager::checkConnection() || !db.open()) {
        setWindowTitle("Connection Error");
        setCentralWidget(new NoConnection(this));
        return;
    }

    setWindowTitle("Clothing FaQTory");

    tabWidget = new QTabWidget;

    tabWidget->addTab(new ProductsTabPage(tabWidget), "Products");
    QIcon clothingIcon(":/assets/icons/tshirt.png");
    tabWidget->setTabIcon(0, clothingIcon);

    tabWidget->addTab(new MaterialsCostTabPage(tabWidget), "Materials Cost");
    QIcon materialsIcon(":/assets/icons/materials_cost.png");
    tabWidget->setTabIcon(1, materialsIcon);

    tabWidget->setIconSize(QSize(35, 35));

    setCentralWidget(tabWidget);
}