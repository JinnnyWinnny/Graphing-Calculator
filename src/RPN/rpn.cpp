#include "rpn.h"
#include <sstream>
#include <math.h>
#include "trig.h"
#include "close.h"
#include "operator.h"
#include "operand.h"
#include "token.h"
#include "unkown.h"
#include "open.h"
#include "../../!include/InputExceptions/inputexceptions.h"


RPN::RPN()
{

}
Queue<Token*> RPN::ShuntingYard(Queue<Token*> input)throw (InputExceptions){
    Stack<Token*> OptorStack;
    Token* p;
    Queue<Token*> outputQ;
    Queue<Token*> result;

    //while input queue is empty
    while(!input.empty()){
        p = input.pop();
        switch (p->TypeOf()) {
        case X:
            //unkown variable
            outputQ.push(p);
            break;
        case OPEN:
            //(
            OptorStack.push(p);
            break;
        case ORAND:
            //operand
            outputQ.push(p);
            break;
        case TRIG:
            //trigonometric
            OptorStack.push(p);
            break;

        case ORATOR:
            if(!OptorStack.empty()){
                int prec = static_cast<Operator*>(p)->precedence();
                int prevPrec = static_cast<Operator*>(OptorStack.top())->precedence();
                //if previous precedence is greater or equal
                if(prevPrec >= prec){
                    outputQ.push(OptorStack.pop());
                }
            }
            else{

            }

            OptorStack.push(p);
            break;
        case CLOSE:
            //pop until ( including open
            while(OptorStack.top()->TypeOf() != OPEN){
                outputQ.push(OptorStack.pop());
                if(OptorStack.empty()){
                    throw InputExceptions();
                }
            }
            break;
        }
    }
    if(!OptorStack.empty()){
        //there are still operator tokens on the stack:
        while(!OptorStack.empty()){
            if(OptorStack.top()->TypeOf() == CLOSE){
                cout<<"missing close par"<<endl;
                throw InputExceptions();

            }else{
                outputQ.push(OptorStack.pop());
            }
        }
    }
    return outputQ;
}
double RPN::eval(Queue<Token*> postfix, double x){
    Stack<Token*> s;
    Token* right;
    Token* left;
    Token* p;
    double d_right = 0;
    double d_left = 0;
    double result = 0;

    while(!postfix.empty()){
        p = postfix.pop();
        switch (p->TypeOf()) {
        case ORAND:     //operand
            s.push(p);
            break;
        case X:         //variable
            s.push(new Operand(x));
            break;
        case TRIG:
            if(s.empty()){
                throw InputExceptions();
            }
            left = s.pop();
            d_left = static_cast<Operand*>(left)->getNum();
            result = static_cast<Trig*>(p)->eval(d_left);
            s.push(new Operand(result));
            break;
        case ORATOR:    //operator
            if(s.empty()){
                throw InputExceptions();
            }
            right = s.pop();

            if(s.empty()){
                throw InputExceptions();
            }
            left = s.pop();
            //convert Token to the Operand
            d_right = static_cast<Operand*>(right)->getNum();
            d_left = static_cast<Operand*>(left)->getNum();
            result = static_cast<Operator*>(p)->eval(d_left,d_right);
            //push into stack
            s.push(new Operand(result));
            break;
        default:
            break;
        }
    }
    return static_cast <Operand*>(s.top())->getNum();

}
Queue<Token*> RPN::strToQ(string input){
    stringstream str(input);
    Queue<Token*> outputQ;
    string each;
    bool neg = false;
    while(str>>each){
        if(isdigit(each.at(0))){
            double temp = stod(each);
            if(neg){
                temp*=-1;
                neg = false;
            }
            outputQ.push(new Operand(temp));
        }
        else if(each == "x"){
//            if(neg){
//                outputQ.push(new Operand(-1));
//                outputQ.push(new Unkown('x'));
//                outputQ.push(new Operator('*'));
//            }else{
                outputQ.push(new Unkown('x'));
//            }
        }
        else if( each == "^"){
            outputQ.push(new Operator(each.at(0)));
        }
        else if(each == "("){
            outputQ.push(new Open());
        }
        else if(each == ")"){
            outputQ.push(new Close());
        }
        else{
            if(each == "sin" || each == "cos" || each == "tan"){
                outputQ.push(new Trig(each));
            }else if(each == "+" || each == "-" ||each == "*" || each == "/"){
//                if(each.at(0) == '-'){
//                    neg = true;
//                }
//                else{
                    outputQ.push(new Operator(each.at(0)));
//                }
            }else{
                throw InputExceptions();
            }
        }
    }
    return outputQ;
}
