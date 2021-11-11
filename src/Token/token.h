#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>

using namespace std;


class Token
{
public:
    Token(){}
    friend ostream& operator<<(ostream& outs, const Token* p){
        p->print(outs);
        return outs;
    }
    virtual void print(ostream& outs = cout)const {
    }
    virtual int TypeOf(){}
};

#endif // TOKEN_H
