//#include "mainwindow.h"

//#include <QApplication>
#include <iostream>
#include <string>
#include "src/core/errors/either.h"

using std::cout;
using std::endl;
using std::to_string;

class Error {
public:
    int a;

    Error(int a = 0) : a(a) {};
};

int main() {
    //    QApplication a(argc, argv);
    //    MainWindow w;
    //    w.show();
    //    return a.exec();
    Either<Error, int> e = Either<Error, int>::ofLeft(Error(1));

    cout << e.isLeft() << endl;
}
