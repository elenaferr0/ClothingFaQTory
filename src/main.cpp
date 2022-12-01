//#include "mainwindow.h"

//#include <QApplication>
//#include <QtDebug>

#include "src/core/containers/map.h"
#include "src/models/clothing_items/jeans.h"
#include "src/models/size.h"

#include <iostream>
using Containers::Map;
using Models::ClothingItems::Jeans;
using Models::Material;
using Models::Size;
using std::cout;
using std::endl;

int main()
{
  //    QApplication a(argc, argv);
  //    MainWindow w;
  //    w.show();
  //    return a.exec();
  Size s = Size(Size::Value::S, 10);
  Material m = Material(Material::Name::DENIM, Material::UnitOfMeasure::CENTIMETER, 10);

  Jeans j = Jeans("red", list(1, m), s, 10, 10, true, true);
  cout << "ciao";
}
