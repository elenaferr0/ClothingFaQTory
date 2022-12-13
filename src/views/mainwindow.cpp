#include "mainwindow.h"
#include<iostream>
#include <QSqlDatabase>
#include <QBoxLayout>
#include <QLabel>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include "no_connection.h"
#include "product_menu.h"

MainWindow::MainWindow(QWidget* parent)
        : QMainWindow(parent) {

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

    db.setDatabaseName("clothingfaqtory");
    db.setHostName("129.152.21.9");
    db.setPort(5432);
    db.setUserName("qtuser");
    db.setPassword("8rF6*%3t8uQV1jYV6U0m");

    if (!db.open()) {
        setWindowTitle("Connection Error");
        setCentralWidget(new NoConnection(this));
        return;
    }

    setWindowTitle("Clothing FaQTory");
    setCentralWidget(new ProductMenu(this));
}