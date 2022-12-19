#include "views/mainwindow.h"

#include <QApplication>
#include <QFontDatabase>
#include <QFile>
#include <QIODevice>
#include "log_handler.h"

int main(int argc, char** argv) {
    qInstallMessageHandler(logHandler);
    QApplication a(argc, argv);

    QFontDatabase::addApplicationFont(":/fonts/inter.ttf");

    QFile file(":/assets/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    a.setStyleSheet(styleSheet);

    MainWindow w;
    w.resize(1024, 512);
    w.show();

    return a.exec();
}
