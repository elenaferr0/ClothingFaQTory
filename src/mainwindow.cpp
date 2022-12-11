#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
#include <QSqlQuery>
#include "./core/db/querybuilder.h"
#include "./services/repositories/hat_repository.h"
#include "./services/repositories/material_repository.h"
#include "./services/repositories/size_repository.h"

using Core::Db::QueryBuilder;
using Core::Db::Expr;
using Services::HatRepository;
using Services::MaterialRepository;
using Services::SizeRepository;

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
        Overalls o;
        Map<int, Overalls> map;
    } else {
        QMessageBox::information(this, "Not connected", "Database Connected Failed");
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

