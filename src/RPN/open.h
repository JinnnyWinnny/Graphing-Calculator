#ifndef OPEN_H
#define OPEN_H
#include "../../!include/Token/token.h"
#include "../../!include/const/RPN_Const/const_rpn.h"


class Open: public Token
{
public:
    Open():_open('('){}
    int TypeOf(){return OPEN;}
    virtual void print(ostream& outs = cout)const{
        outs<<_open;
    }

private:
    char _open;
};

#endif // OPEN_H
