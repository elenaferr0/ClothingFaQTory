#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include<iostream>

MainWindow::MainWindow(QWidget* parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

    db.setDatabaseName("clothingfaqtory");
    db.setHostName("129.152.21.9");
    db.setPort(5432);
    db.setUserName("qtuser");
    db.setPassword("8rF6*%3t8uQV1jYV6U0m");

    if (db.open()) {
        QMessageBox::information(this, "Connection", "Database connection success");
        QVector <QString> tables = db.tables().toVector();
        for (auto t = tables.begin(); t != tables.end(); t++) {
            std::cout << (*t).toStdString() << " ";
        }
    } else {
        QMessageBox::information(this, "Not connected", "Database Connected Failed");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

