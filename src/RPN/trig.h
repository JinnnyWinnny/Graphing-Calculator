#ifndef TRIG_H
#define TRIG_H
#include "../../!include/Token/token.h"
#include "../../!include/const/RPN_Const/const_rpn.h"
#include <cmath>

class Trig: public Token
{
public:
    Trig();
    Trig(string sct):_sct(sct){}
    int TypeOf(){return TRIG;}
    virtual void print(ostream& outs = cout)const{
        outs<<_sct;
    }
    double eval(double left){
        if(_sct == "sin"){
            return sin(left);
        }
        else if(_sct == "cos"){
            return cos(left);
        }
        return tan(left);
    }


private:
    string _sct;
};

#endif // TRIG_H
