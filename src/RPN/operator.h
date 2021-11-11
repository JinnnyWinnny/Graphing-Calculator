#ifndef OPERATOR_H
#define OPERATOR_H
#include "../../!include/Token/token.h"
#include "../../!include/const/RPN_Const/const_rpn.h"

class Operator: public Token
{
public:
    Operator();
    Operator(char op);
    void print(ostream& outs = cout)const{
        outs<<_op;
    }
    int TypeOf(){return ORATOR;}
    char OperatorOnly(){return _op;}
    int precedence();
    double eval(double left, double right);

private:
    char _op;

};

#endif // OPERATOR_H
