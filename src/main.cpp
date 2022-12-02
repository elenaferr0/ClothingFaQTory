//#include "mainwindow.h"

//#include <QApplication>
#include <iostream>
#include <string>
#include "src/core/orm/querybuilder.h"
#include "src/core/orm/expression.h"
using Core::Orm::QueryBuilder;
using Core::Orm::Expr;
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

  string query = qb.select()
      .from("users", "us")
      .join(QueryBuilder::Join::INNER,
	    "animals",
	    Expr("a.user_id").equals({"u.id"}).andX(Expr("u.id").equals({"4"})))
      .where(
	Expr("u.username").equals({":username"})
	  .andX(
	    Expr("u.stupid")
	    .orX(Expr("u.age").geq({":age"}))
	  )
      )
      .orderBy("a.user_id", QueryBuilder::ASC)
      .limit(10)
      .bindParameters(params)
      .build();

  cout << query;
}
