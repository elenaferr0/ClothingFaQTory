#include "mainwindow.h"

#include <QApplication>
#include <QtDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QtPrivate::RefCount
    w.show();
    return a.exec();
}
