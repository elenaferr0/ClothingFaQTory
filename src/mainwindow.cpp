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
      QueryBuilder builder;
      SizeRepository sr = SizeRepository("size");
      Either <Error, Size> size = sr.findById(1);
      Either <Error, list<Size>> sizes = sr.findAll();
      if (size.isLeft()) {

      }
  } else {
    QMessageBox::information(this, "Not connected", "Database Connected Failed");
  }
}

MainWindow::~MainWindow()
{
  delete ui;
}

