#ifndef QUERYBUILDER_H
#define QUERYBUILDER_H
#include <string>
#include <vector>
#include "src/core/containers/map.h"
#include "src/core/db/expression.h"

using std::string;
using Core::Containers::Map;
using std::vector;
using Core::Db::Expr;


namespace Core::Db {
class QueryBuilder {
  public:
    enum Join {
      INNER, OUTER, LEFT, RIGHT
    };
    enum Order {
      ASC, DESC
    };

    friend string operator+(string, const list <string>&);

    QueryBuilder() : query() {};

    // qb.select("u");
    QueryBuilder& select(string field = "*", string alias = "");

    QueryBuilder& count(string field = "*");

    // qb.select({("username", "u"), ("email", "e")});
    // takes fields with aliases as input (the alias can also be empty)
    QueryBuilder& select(const Map <string, string>& fields);

    // does not override previous select
    QueryBuilder& addSelect(string field = "*", string alias = "");

    // qb.delete();
    QueryBuilder& deleteT();

    // qb.update("username", "u");
    QueryBuilder& update(string entity);

    // qb.insertInto("username");
    QueryBuilder& insertInto(string entity, const Map <string, string>& fields);

    // qb.set("u.username", "foo");
    QueryBuilder& set(string field, string value);

    // qb.set({("username", "u"), ("email", "e")})
    QueryBuilder& set(const Map <string, string>& fields);

    // qb.from("User", "u");
    QueryBuilder& from(string from, string alias = "");

    // qb.join("User", "u.username = 'foo'");
    QueryBuilder& join(Join type, string table, const Expr&);

    // overrides previous where statements
    // qb.where("u.username" = 'foo')
    QueryBuilder& where(const Expr&);

    QueryBuilder& andX(const Expr&);
    QueryBuilder& orX(const Expr&);
    QueryBuilder& notX(const Expr&);

    // qb.orderBy("u.username")
    // qb.orderBy("u.username", "DESC")
    QueryBuilder& orderBy(string field, Order order = Order::ASC);

    // qb.limit(1);
    QueryBuilder& limit(int maxResults);

    // qb.setParameter("id", 1);
    QueryBuilder& bindParameter(string key, string value);

    QueryBuilder& bindParameters(const Map<string, string>& params);


    string build();
  private:
    string toString(Join joinType);
    string toString(Order order);
    string query;
};
}
#endif // QUERYBUILDER_H
