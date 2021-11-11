#include "operator.h"
#include <cmath>

Operator::Operator():_op(' '){}
Operator::Operator(char op):_op(op){}
double Operator::eval(double left, double right){
    double result = 0;
    switch (_op) {
    case '+':
        result = left+right;
        break;
    case '-':
        result = left-right;
        break;
    case '*':
        result = left*right;
        break;
    case '/':
        result = left/right;
        break;
    case '^':
        result = pow(left,right);
        break;

    default:
        break;
    }

    return result;
}
int Operator::precedence(){

    switch (_op) {
    case '*':
        return  3;
    case '/':
        return  3;
    case '+':
        return  2;
    case '-':
        return  2;
    case '^':
        return 4;
    default:
        return 0;
    }

}
