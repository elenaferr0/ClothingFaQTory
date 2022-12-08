#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include<iostream>
#include <QSqlQuery>
#include <QSqlRecord>
#include "src/core/db/querybuilder.h"
#include "src/core/db/expression.h"
#include "src/services/repositories/material_repository.h"

using Core::Db::QueryBuilder;
using Core::Db::Expr;
using Services::MaterialRepository;

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
//	QMessageBox::information(this, "Connection", "Database connection success");
	MaterialRepository mr;
	Material m;
	m.setName("WOOL");
	m.setCostPerUnit(20);
	m.setUnitOfMeasure("cm");

	Either<Error, Material> e = mr.save(m);
	qInfo() << QString::fromStdString(e.isLeft() ? e.left().value().getMessage() : "");

    } else {
	QMessageBox::information(this, "Not connected", "Database Connected Failed");
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

