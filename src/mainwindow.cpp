#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include<iostream>
#include <QSqlQuery>

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

    QSqlQuery query = db.exec("select * from \"size\"");

    while (query.next()) {
      QString q = query.value(1).toString();
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

