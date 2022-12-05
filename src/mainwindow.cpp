#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include<iostream>
#include <QSqlQuery>
#include <QSqlRecord>
#include "src/core/db/querybuilder.h"
#include "src/core/db/expression.h"
using Core::Db::QueryBuilder;
using Core::Db::Expr;

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
    //        QMessageBox::information(this, "Connection", "Database connection success");
    QueryBuilder builder;

    QSqlQuery query;
    QString sql = QString::fromStdString(builder.select()
						.from("size")
						.join(QueryBuilder::INNER, "product", Expr("s.id").equals({"p.size_id"}))
						.build());
    qInfo() << sql;
    query.exec(sql);

    while (query.next()) {
      QString q = query.value("id").toString();
      q = query.value("id").toString();
      qDebug() << q;
    }

  } else {
    QMessageBox::information(this, "Not connected", "Database Connected Failed");
  }
}

MainWindow::~MainWindow()
{
  delete ui;
}

