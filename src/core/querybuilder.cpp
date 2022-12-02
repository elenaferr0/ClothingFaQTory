#include "querybuilder.h"
#include <ostream>

using std::ostringstream;
using Core::QueryBuilder;

QueryBuilder& QueryBuilder::select(string field, string alias){
  // SELECT field
  query = "SELECT " + field == "" ? "*" : field;

  if(alias != ""){
    query += " AS " + alias;
  }

  query += "\n";
  return *this;
}


QueryBuilder& QueryBuilder::select(Map<string, string> fields){
  if(fields.empty()){
    return *this;
  }

  query = "SELECT ";

  for(auto f = fields.begin(); f != fields.end(); ++f){

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
  query += ", " + field;

  if(alias != ""){
    query += " AS " + alias;
  }

  query += "\n";
  return *this;
}

QueryBuilder& QueryBuilder::deleteEntity(string field){
  query = "DELETE " + field + "\n";
  return *this;
}

QueryBuilder& QueryBuilder::update(string entity){
  query = "UPDATE " + entity + "\n";
  return *this;
}

QueryBuilder& QueryBuilder::set(string field, string value){
  query = "SET " + field + " = " + value;
  return *this;
}

QueryBuilder& QueryBuilder::set(Map<string, string> fields){
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


QueryBuilder& QueryBuilder::join(JoinType type, string table, string condition){
  if(table == "" || condition == ""){
    return *this;
  }
  query += toString(type) + " JOIN " + table + " ON " + condition + "\n";
  return *this;
}

string QueryBuilder::toString(JoinType joinType){
  switch(joinType){
  case INNER:
    return "INNER";
  case OUTER:
    return "OUTER";
  case LEFT:
    return "LEFT";
  case RIGHT:
    return "RIGHT";
  }
}
