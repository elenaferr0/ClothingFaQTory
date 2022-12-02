#ifndef QUERYBUILDER_H
#define QUERYBUILDER_H
#include <string>
#include <vector>
#include "src/core/containers/map.h"

using std::string;
using Containers::Map;
using std::vector;

namespace Utils::Orm {
class QueryBuilder
{
    string query;
  public:
    enum Join {INNER, OUTER, LEFT, RIGHT};
    enum Order {ASC, DESC};

    QueryBuilder() : query(){};

    // qb.select("u");
    QueryBuilder& select(string field = "*", string alias = "");

    // qb.select({("username", "u"), ("email", "e")});
    // takes fields with aliases as input (the alias can also be empty)
    QueryBuilder& select(const Map<string, string>& fields);

    // does not override previous select
    QueryBuilder& addSelect(string field = "*", string alias = "");

    // qb.delete("u");
    QueryBuilder& deleteEntity(string entity);

    // qb.update("username", "u");
    QueryBuilder& update(string entity);

    // qb.set("u.username", "foo");
    QueryBuilder& set(string field, string value);

    // qb.set({("username", "u"), ("email", "e")})
    QueryBuilder& set(const Map<string, string>& fields);

    // qb.from("User", "u");
    QueryBuilder& from(string from, string alias = "");

    // qb.join("User", "u.username = 'foo'");
    QueryBuilder& join(Join type, string table, string condition);

    // overrides previous where statements
    // qb.where("u.username" = 'foo')
    QueryBuilder& where(string evaluation);

    QueryBuilder& andCondition(string evaluation);
    QueryBuilder& orCondition(string evaluation);
    QueryBuilder& notCondition(string evaluation);

    // qb.orderBy("u.username")
    // qb.orderBy("u.username", "DESC")
    QueryBuilder& orderBy(string field, Order order = Order::ASC);

    // qb.limit(1);
    QueryBuilder& limit(int maxResults);

    // qb.setParameter("id", 1);
    QueryBuilder& bindParameter(string key, string value);

    QueryBuilder& bindParameters(const Map<string, string>& params);


    string build();

    string toString(Join joinType);
    string toString(Order order);
};
}

#endif // QUERYBUILDER_H
