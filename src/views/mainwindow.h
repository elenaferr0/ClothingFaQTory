#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSqlDatabase>
#include <QMainWindow>
#include <QMessageBox>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Views { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT
private:
    QTabWidget* tabWidget;
public:
    MainWindow(QWidget* parent = nullptr);
};

#endif // MAINWINDOW_H
