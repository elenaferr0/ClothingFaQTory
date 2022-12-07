#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include<iostream>
#include <QSqlQuery>
#include <QSqlRecord>
#include "src/core/db/querybuilder.h"
#include "src/core/db/expression.h"
#include "src/services/repositories/sizerepository.h"

using Core::Db::QueryBuilder;
using Core::Db::Expr;
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
//    QMessageBox::information(this, "Connection", "Database connection success");
	SizeRepository sr("size");
	Either <Error, Size> eos = sr.findById(1);
	if (eos.isRight()) {
	    Size size = eos.right().value();
	    size.setName("XS");
	    size.setExtraPercentageOfMaterial(0);
	    eos = sr.save(size);
	    qInfo() << eos.isLeft();
	}

	QSqlQuery query;
	QVariantList list;
	list << "2oee" << 0 << 7;
	query.prepare("update size set name = ?, extra_percentage_of_material = ? where (id = ?);");

//	for(int i = 0; i < list.count(); i++){
//	  query.bindValue(i, list.at(i));
//	}
//	query.exec();

	query.addBindValue(list);
	query.execBatch();
	qInfo() << query.lastError() << query.lastError().type() << query.lastError().text();
	qInfo() << query.isValid();
    } else {
        QMessageBox::information(this, "Not connected", "Database Connected Failed");
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

