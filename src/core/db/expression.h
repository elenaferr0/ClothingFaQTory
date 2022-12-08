#ifndef Expr_H
#define Expr_H

#include <string>
#include <list>

using std::string;
using std::list;

namespace Core::Db {
    class Expr {
    private:
        string expression;
    public:
        friend string operator+(string, const Expr&);

        friend string operator+(string, list<int>&);

        // allows implicit constructor
        Expr(string initial = "") : expression(initial) {};

        Expr& andX(const Expr&);

        Expr& orX(const Expr&);

        Expr& notX();

        Expr& equals(const Expr&);

        Expr& notEquals(const Expr&);

        Expr& in(const list<int>&);

        Expr& gt(const Expr&);    // greater than
        Expr& geq(const Expr&); // greater or eq than
        Expr& lt(const Expr&);    // less than
        Expr& leq(const Expr&); // less or eq than
        Expr& isNull();

        Expr& isNotNull();

        Expr& like(string);
    };
}

#endif // Expr_H
