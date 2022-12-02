#ifndef QUERYBUILDER_H
#define QUERYBUILDER_H
#include <string>
#include <vector>
#include "src/core/containers/map.h"

using std::string;
using Containers::Map;
using std::vector;

namespace Core{
class QueryBuilder
{
    string query;
  public:
    enum JoinType {INNER, OUTER, LEFT, RIGHT};

    QueryBuilder() : query(){};

    // qb.select("u");
    QueryBuilder& select(string field = "*", string alias = "");

    // qb.select({("username", "u"), ("email", "e")});
    // takes fields with aliases as input (the alias can also be empty)
    QueryBuilder& select(Map<string, string> fields);

    // does not override previous select
    QueryBuilder& addSelect(string field = "*", string alias = "");

    // qb.delete("u");
    QueryBuilder& deleteEntity(string entity);

    // qb.update("username", "u");
    QueryBuilder& update(string entity);

    // qb.set("u.username", "foo");
    QueryBuilder& set(string field, string value);

    // qb.set({("username", "u"), ("email", "e")})
    QueryBuilder& set(Map<string, string> fields);

    // qb.from("User", "u");
    QueryBuilder& from(string from, string alias = "");

    // qb.join("User", "u.username = 'foo'");
    QueryBuilder& join(JoinType type, string table, string condition);

    // overrides previous where statements
    // qb.where("u.username" = 'foo')
    QueryBuilder& where(string condition);

    // does not override previous statements
    // qb.where("u.username" = 'foo').andWhere("u.age > 1");
    QueryBuilder& andWhere(string condition);

    // does not override previous statements
    // qb.where("u.username" = 'foo').orWhere("u.age > 1");
    QueryBuilder& orWhere(string condition);

    // qb.orderBy("u.username")
    // qb.orderBy("u.username", "DESC")
    QueryBuilder& orderBy(string field, string order = "ASC");

    // qb.limit(1);
    QueryBuilder& limit(int maxResults);

    // qb.setParameter("id", 1);
    QueryBuilder& setParameter(string key, string value);

    QueryBuilder& setParameters(Map<string, string> parameters);


    string build();
};
}

#endif // QUERYBUILDER_H
