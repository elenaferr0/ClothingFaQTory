#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <string>

using std::string;

class Expression
{
  private:
    string expression;
  public:
    friend string operator+(string, const Expression&);

    Expression(string initial = "") : expression(initial){};
    Expression& andX(const Expression&);
    Expression& orX(const Expression&);
    Expression& notX(const Expression&);
    Expression& equal(const Expression&);
//    Expression& notEqual(const Expression&);
//    Expression& gt(const Expression&);	// greater than
//    Expression& geq(const Expression&); // greater or eq than
//    Expression& lt(const Expression&);	// less than
//    Expression& leq(const Expression&); // less or eq than
//    Expression& isNull(const Expression&);
//    Expression& isNotNull();
//    Expression& like();
};

#endif // EXPRESSION_H
