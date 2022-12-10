#include "querybuilder.h"
#include <string>
#include <regex>

using std::to_string;
using std::regex;
using Core::Db::QueryBuilder;
using Core::Containers::Map;

QueryBuilder& QueryBuilder::select(string field, string alias) {
    if (field == "") {
        return *this;
    }

    query = "SELECT " + field + (field == "*" ? "" : " " + alias) + " ";
    return *this;
}

QueryBuilder& QueryBuilder::count(string field) {
    query = "COUNT (" + field + ") ";
    return *this;
}

QueryBuilder& QueryBuilder::select(const Map<string, string>& fields) {
    if (fields.empty()) {
        return *this;
    }

    query = "SELECT ";

    for (auto f = fields.begin(); f != fields.end(); ++f) {

        query += (*f).first;
        // create automatically the alias if the second parameter is not present
        query += " " + (*f).second == "" ? to_string((*f).first[0]) : (*f).second;
        query += ", ";
    }

    // remove the last comma
    query = query.substr(0, query.length() - 2) + " ";
    return *this;
}

QueryBuilder& QueryBuilder::addSelect(string field, string alias) {
    if (field == "") {
        return *this;
    }

    if (alias == "") {
        alias = field[0];
    }

    query += ", " + field + " " + alias + " ";
    return *this;
}

QueryBuilder& QueryBuilder::insertInto(string entity, const list<string>& fieldNames) {
    query = "INSERT INTO " + entity; // + "()"
    string names = "(", values = "(";

    for (auto f = fieldNames.begin(); f != fieldNames.end(); ++f) {
        names += (*f) + ",";
        values += "?,";
    }

    names = names.substr(0, names.size() - 1) + ")"; // remove last comma
    values = values.substr(0, values.size() - 1) + ")";
    query += names + " VALUES " + values;
    return *this;
}

QueryBuilder& QueryBuilder::deleteT() {
    query = "DELETE ";
    return *this;
}

QueryBuilder& QueryBuilder::update(string entity) {
    if (entity != "") {
        query = "UPDATE " + entity + " ";
    }
    return *this;
}

QueryBuilder& QueryBuilder::set(string field) {
    if (field != "") {
        query += "SET " + field + " = ? ";
    }
    return *this;
}

QueryBuilder& QueryBuilder::set(const list<string>& fieldNames) {
    if (fieldNames.empty()) {
        return *this;
    }

    query += "SET ";
    auto f = fieldNames.begin();

    for (; f != fieldNames.end(); ++f) {
        query += (*f) + " = ?, ";
    }

    query = query.substr(0, query.size() - 2) + " "; // remove last comma
    return *this;
}

QueryBuilder& QueryBuilder::from(string from, string alias) {
    if (from == "" || (alias == "" && from == "*")) {
        return *this;
    }

    if (alias == "") {
        alias = from[0];
    }

    query += "FROM " + from + " " + alias + " ";
    return *this;
}


QueryBuilder& QueryBuilder::join(Join type, string table, const Expr& x) {
    if (table != "") {
        query += toString(type) + " JOIN " + table + " " + table[0] + " ON " + x + " ";
    }
    return *this;
}

QueryBuilder& QueryBuilder::where(const Expr& x) {
    query += "WHERE " + x + " ";
    return *this;
}

QueryBuilder& QueryBuilder::orderBy(string field, Order order) {
    if (field != "") {
        query += "ORDER BY " + field + " " + toString(order) + " ";
    }
    return *this;
}

QueryBuilder& QueryBuilder::limit(int maxResults) {
    if (maxResults > 0) {
        query += "LIMIT " + to_string(maxResults);
    }

    return *this;
}

QueryBuilder& QueryBuilder::andX(const Expr& x) {
    query += "AND " + x + " ";
    return *this;
}

QueryBuilder& QueryBuilder::orX(const Expr& x) {
    query += "OR " + x + " ";
    return *this;
}

QueryBuilder& QueryBuilder::notX(const Expr& x) {
    query += "NOT " + x + " ";
    return *this;
}

QueryBuilder& QueryBuilder::bindParameter(string key, string value) {
    query = regex_replace(query, regex(key), value);
    return *this;
}

QueryBuilder& QueryBuilder::bindParameters(const Map<string, string>& params) {
    for (auto it = params.begin(); it != params.end(); it++) {
        bindParameter((*it).first, (*it).second);
    }

    return *this;
}

string QueryBuilder::build() {
    string copy = query + ";";
    query = "";
    return copy;
}

string QueryBuilder::toString(Join joinType) {
    switch (joinType) {
        case INNER:
            return "INNER";
        case OUTER:
            return "OUTER";
        case LEFT:
            return "LEFT";
        case RIGHT:
        default:
            return "RIGHT";
    }
}

string QueryBuilder::toString(Order order) {
    if (order == Order::ASC) {
        return "ASC";
    }

    return "DESC";
}
