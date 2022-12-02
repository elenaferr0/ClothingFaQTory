//#include "mainwindow.h"

//#include <QApplication>
#include <iostream>
#include <string>
#include "src/utils/querybuilder.h"
using Utils::QueryBuilder;
using std::cout;
using std::to_string;

int main()
{
  //    QApplication a(argc, argv);
  //    MainWindow w;
  //    w.show();
  //    return a.exec();

  QueryBuilder qb = QueryBuilder();
  Map<string, string> params;
  params["username"] = "foo";
  params["age"] = to_string(13);
  params["name"] = "dog";

  string query = qb.select("username", "u")
      .from("users", "u")
      .join(QueryBuilder::INNER, "animals", "a.user_id = u.id")
      .where("u.username = :username")
      .andCondition("a.name = :name")
      .andCondition("u.age > :age")
      .limit(10)
      .bindParameters(params)
      .build();

  cout << query;
}
