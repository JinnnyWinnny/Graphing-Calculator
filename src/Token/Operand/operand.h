#ifndef OPERAND_H
#define OPERAND_H
#include "../../!include/Token/token.h"
#include "../../!include/const/RPN_Const/const_rpn.h"

class Operand: public Token
{
public:
    Operand();
    Operand(double newNum);
    virtual void print(ostream& outs = cout)const{
        outs<<_num;
    }
    int TypeOf(){return ORAND;}
    double getNum(){return _num;}
private:
    double _num;
};

#endif // OPERAND_H
