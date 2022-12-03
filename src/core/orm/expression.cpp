#include "expression.h"
#include <string>
using std::string;
using std::to_string;
using Core::Orm::Expr;

namespace Core::Orm {
  string operator+(string s, const Expr& x){
      return s + x.expression;
  }

  string operator+(string s, const list<int>& expr){

    for(auto it = expr.begin(); it != expr.end(); it++){
      s += to_string(*it) + ", ";
    }

    return s.substr(0, s.size() - 2); // remove last comma
  }
}

Expr& Expr::andX(const Expr& x){
  expression = "(" + expression + " AND " + x + ")";
  return *this;
}

Expr& Expr::orX(const Expr& x){
  expression = "(" + expression + " OR " + x + ")";
  return *this;
}

Expr& Expr::notX(){
  expression += "(NOT " + expression + ")";
  return *this;
}

Expr& Expr::equals(const Expr& x){
  expression = "(" + expression + " = " + x + ")";
  return *this;
}

Expr& Expr::notEquals(const Expr& x){
  expression = "(NOT" + expression + " = " + x + ")";
  return *this;
}

Expr& Expr::in(list<int>& s){
  expression += " IN (" + s + ")";
  return *this;
}

Expr& Expr::gt(const Expr& x){
  expression = "(" + expression + " > " + x + ")";
  return *this;
}

Expr& Expr::geq(const Expr& x){
  expression = "(" + expression + " >= " + x + ")";
  return *this;
}

Expr& Expr::lt(const Expr& x){
  expression = "(" + expression + " < " + x + ")";
  return *this;
}

Expr& Expr::leq(const Expr& x){
  expression = "(" + expression + " <= " + x + ")";
  return *this;
}

Expr& Expr::isNull(){
  expression = "(" + expression + " IS NULL)";
  return *this;
}

Expr& Expr::isNotNull(){
  expression = "(" + expression + " IS NOT NULL)";
  return *this;
}

Expr& Expr::like(string s){
  expression = "(" + expression + " LIKE " + s + ")";
  return *this;
}
