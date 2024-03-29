
#include <QApplication>
#include <QFontDatabase>
#include <QFile>
#include <QIODevice>
#include "log_handler.h"
#include "views/main_view.h"

using Views::MainView;

int main(int argc, char** argv) {
    qInstallMessageHandler(logHandler);
    QApplication a(argc, argv);

    QFontDatabase::addApplicationFont(":/fonts/inter.ttf");

    QFile file(":/assets/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    a.setStyleSheet(styleSheet);

    MainView w;
    w.resize(1300, 512);
    w.show();

    return a.exec();
}
