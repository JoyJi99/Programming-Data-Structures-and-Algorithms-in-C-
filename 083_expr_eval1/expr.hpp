#include <iostream>
#include <ctype.h>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <sstream>
class Expression{
public:
     virtual std::string toString() const = 0;
     virtual ~Expression(){}
};

class NumExpression : public Expression{
protected:
    long numExpr;
public:
    NumExpression(long num):numExpr(num){}

    virtual std::string toString() const{
        std::stringstream ss;
        ss << numExpr;
        return ss.str();
    }

    virtual ~NumExpression(){}
};

class PlusExpression : public Expression{
protected:
    Expression *l;
    Expression *r;
public:
    PlusExpression(Expression * lhs, Expression * rhs): l(lhs), r(rhs){}
    virtual std::string toString() const{
        std::stringstream ss;
        ss << "( " << l->toString() << " + " << r->toString() << " )";
        return ss.str();
    }
    virtual  ~PlusExpression(){
        delete l;
        delete r;
    }
};
