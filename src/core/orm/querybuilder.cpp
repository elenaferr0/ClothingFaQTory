#include "querybuilder.h"
#include <string>
#include <regex>

using std::to_string;
using std::regex;
using Utils::Orm::QueryBuilder;

QueryBuilder& QueryBuilder::select(string field, string alias){
  if(field == ""){
    return *this;
  }

  query = "SELECT " + (field == "" ? "*" : field);

  if(alias != ""){
    query += " AS " + alias;
  }

  query += "\n";
  return *this;
}


QueryBuilder& QueryBuilder::select(const Map<string, string>& fields){
  if(fields.empty()){
    return *this;
  }

  query = "SELECT ";

  for(auto f = fields.cbegin(); f != fields.cend(); ++f){

    query += (*f).first;

    if((*f).second != ""){
      query += " AS " + (*f).second;
    }

    query += ", ";
  }

  // remove the last comma
  query = query.substr(0, query.length() - 2) + "\n";
  return *this;
}

QueryBuilder& QueryBuilder::addSelect(string field, string alias){
  if(field == ""){
    return *this;
  }

  query += ", " + field;

  if(alias != ""){
    query += " AS " + alias;
  }

  query += "\n";
  return *this;
}

QueryBuilder& QueryBuilder::deleteEntity(string field){
  if(field != ""){
    query = "DELETE " + field + "\n";
  }
  return *this;
}

QueryBuilder& QueryBuilder::update(string entity){
  if(entity != ""){
    query = "UPDATE " + entity + "\n";
  }
  return *this;
}

QueryBuilder& QueryBuilder::set(string field, string value){
  if(field != "" && value != ""){
    query = "SET " + field + " = " + value;
  }
  return *this;
}

QueryBuilder& QueryBuilder::set(Map<string, string> fields){
  if(fields.empty()){
    return *this;
  }

  query += "SET ";

  for(auto f = fields.begin(); f != fields.end(); ++f){
    query += (*f).first + " = " + (*f).second + ", ";
  }

  // remove the last comma
  query = query.substr(0, query.length() - 2) + "\n";
  return *this;
}

QueryBuilder& QueryBuilder::from(string from, string alias){
  query += "FROM " + from;

  if (alias != ""){
    query += " AS " + alias;
  }

  query += "\n";
  return *this;
}


QueryBuilder& QueryBuilder::join(Join type, string table, string condition){
  if(table != "" || condition != ""){
    query += toString(type) + " JOIN " + table + " ON " + condition + "\n";
  }
  return *this;
}

QueryBuilder& QueryBuilder::where(string evaluation){
  if(evaluation != ""){
    query += "WHERE " + evaluation + "\n";
  }

  return *this;
}

QueryBuilder& QueryBuilder::andCondition(string evaluation){
  if(evaluation != ""){
    query += "AND " + evaluation + "\n";
  }

  return *this;
}

QueryBuilder& QueryBuilder::orCondition(string evaluation){
  if(evaluation != ""){
    query += "OR " + evaluation + "\n";
  }

  return *this;
}

QueryBuilder& QueryBuilder::notCondition(string evaluation){
  if(evaluation != ""){
    query += "NOT " + evaluation + "\n";
  }

  return *this;
}


QueryBuilder& QueryBuilder::orderBy(string field, Order order){
  if (field != ""){
    query += "ORDER BY " + field + " " + toString(order);
  }
  return *this;
}

QueryBuilder& QueryBuilder::limit(int maxResults){
  if(maxResults > 0){
    query += "LIMIT " + to_string(maxResults);
  }

  return *this;
}

QueryBuilder& QueryBuilder::bindParameter(string key, string value){
  query = regex_replace(query, regex(":" + key), "\"" + value + "\"");
  return *this;
}

QueryBuilder& QueryBuilder::bindParameters(const Map<string, string>& params){
  for(auto it = params.cbegin(); it != params.cend(); it++){
    bindParameter((*it).first, (*it).second);
  }

  return *this;
}

string QueryBuilder::build(){
  return query + ";";
}

string QueryBuilder::toString(Join joinType){
  switch(joinType){
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

string QueryBuilder::toString(Order order){
  if(order == Order::ASC){
    return "ASC";
  }

  return "DESC";
}
