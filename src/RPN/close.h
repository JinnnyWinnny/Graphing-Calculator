#ifndef CLOSE_H
#define CLOSE_H
#include "../../!include/Token/token.h"
#include "../../!include/const/RPN_Const/const_rpn.h"

class Close: public Token
{
public:
    Close():_close(')'){}
    int TypeOf(){return CLOSE;}
    virtual void print(ostream& outs = cout)const{
        outs<<_close;
    }

private:
    char _close;
};

#endif // CLOSE_H
