#ifndef RPN_H
#define RPN_H

#include "../../!include/Token/token.h"
#include "../../!include/queue/queue.h"
#include "../../!include/Stack/stack.h"
#include "../../!include/InputExceptions/inputexceptions.h"



class RPN
{
public:
    RPN();
    double eval(Queue<Token*> postfix, double x);
    Queue<Token*> ShuntingYard(Queue<Token*> input)throw(InputExceptions);
    Queue<Token*> strToQ(string input);


};

#endif // RPN_H
