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
        MaterialRepository* mr = MaterialRepository::getInstance();
        HatRepository* hr = HatRepository::getInstance();
        SizeRepository* sr = SizeRepository::getInstance();

        Either<Error, Hat> h = hr->findById(2);
        h.forceRight().setMaterial(mr->findByName(Material::WOOL).forceRight());

        Hat h2 = Hat(-1,
                     "CODE",
                     "PINK",
                     mr->findByName(Material::COTTON).forceRight(),
                     sr->findByName(Size::ONE_SIZE).forceRight()
        );
        list<Hat> l;
        l.push_back(h.forceRight());
        l.push_back(h2);
        hr->saveAll(l);

    } else {
        QMessageBox::information(this, "Not connected", "Database Connected Failed");
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

