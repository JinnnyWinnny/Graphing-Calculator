#ifndef UNKOWN_H
#define UNKOWN_H
#include "../../!include/Token/token.h"
#include "../../!include/const/RPN_Const/const_rpn.h"

class Unkown: public Token
{
public:
    Unkown():_x(' '){}
    Unkown(char x):_x(x){}
    virtual void print(ostream& outs = cout)const{
        outs<<_x;
    }
    int TypeOf(){return X;}

private:
    char _x;
};

#endif // UNKOWN_H
