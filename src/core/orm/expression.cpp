#include "expression.h"

string operator+(string s, const Expression& x){
    return s + x.expression;
}

Expression& Expression::andX(const Expression& x){
  expression += " AND " + x;
  return *this;
}

Expression& Expression::orX(const Expression& x){
  expression += " OR " + x;
  return *this;
}

Expression& Expression::notX(const Expression& x){
  expression += " OR " + x;
  return *this;
}

Expression& Expression::equal(const Expression& x){
  expression += " = " + x;
  return *this;
}
