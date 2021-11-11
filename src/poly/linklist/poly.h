#ifndef POLY_H
#define POLY_H
#include "../../!include/list/list.h"
#include "../../!include/term/termlinklist.h"
#include "../../!include/sorted_unique/sorted_unique/list.h"

class Poly
{
public:

    Poly();
    Poly(int term_array[], int order);

    Poly(const Poly &copyThis);
    Poly& operator =(const Poly& right);

    Poly& operator +=(const Term& t);
    Poly& operator *=(const Term& t);
    friend Poly operator + (const Poly& left, const Term& t);
    friend Poly operator * (const Poly& left, const Term& t);

    Poly& operator +=(const Poly& right);
    Poly& operator *=(const Poly& right);
    Poly& operator -=(const Poly& right);
    Poly& operator /=(const Poly& right);

    friend Poly operator + (const Poly& left, const Poly& right);
    friend Poly operator -(const Poly& left, const Poly& right);
    friend Poly operator * (const Poly& left, const Poly& right);
    friend Poly operator / (const Poly& left, const Poly& right);
    Poly operator -() const;

    void fix_order();

    friend ostream& operator << (ostream& outs, const Poly& print_me);
    friend istream& operator >> (istream& outs, Poly& print_me);

    const Term& operator [](const int exp) const;
    Term& operator [](const int exp);
private:
    List<Term> _poly;  //descending sorted list
    int _order;
};

Poly::Poly(){
    _order = 0;
}
Poly::Poly(int term_array[], int order){
    _order = order;
    //store each coefs in the term and then insert head
    for(int i=0; i<=order; i++){
        Term t(term_array[i],i);
        _poly.InsertHead(t);
    }
    fix_order();
}
Poly::Poly(const Poly &copyThis){
    _order = copyThis._order;
    _poly = copyThis._poly;
}
Poly& Poly::operator =(const Poly& right){

    if(this == &right){
        return *this;
    }
    _order = right._order;
    _poly = right._poly;
    return *this;
}
const Term& Poly::operator [](const int exp) const{
    return _poly[_order-exp];
}
Term& Poly::operator [](const int exp){
    return _poly[_order-exp];
}
istream& operator >>(istream& ins, Poly& p){
    Term t;
    Poly newP;
    do{
        //get a term
        ins>>t;
        //put it into the empty poly
        newP += t;
    }while(t._exp != 0);
    p = newP;
    return ins;
}

ostream& operator << (ostream& outs, const Poly& print_me){
    node<Term>* walker =
            print_me._poly.Begin();
    while(walker != nullptr){
        cout<<walker->_item;
        walker = walker->_next;
    }
    return outs;
}

Poly& Poly::operator +=(const Term& t){
    //this poly * t;
    *this = *this + t;
    return *this;
}
Poly operator * (const Poly& left, const Term& t){
    Poly result(left);  //copy left
    //multiply term to each term of left
    for(int i = 0; i<=result._order; i++){
        result._poly[i] = result._poly[i] * t;
    }
    return result;
}
Poly& Poly::operator *=(const Term& t){
    //this poly * t;
    *this = *this * t;
    return *this;
}
Poly operator + (const Poly& left, const Term& t){
    if(left._order>0){  //when left is not an empty poly
        Poly result(left);
        //if term already exists in poly add it
        if(result._poly.Search(t) == nullptr){
            result._poly.UniqueSorted(t);
        }
        //else insert it
        else{
            result._poly.addInsert(t);
        }
        return result;
    }
    else {   //left is an empty poly
        Poly result;
        for(int i=0; i<t._exp; i++){
            //making terms with zero coef
            Term termWzero(0,i);
            //insert zero terms at the head up to the
            // < exp of t
            result._poly.InsertHead(termWzero);
        }
        result._poly.InsertHead(t);
        result._order = t._exp;
        return result;
    }
}
Poly operator + (const Poly& left, const Poly& right){
    //left is not an empty poly
    if(left._order>0){
        Poly result(left);
        //add each term of right to the left
        for(int i=0; i<=right._order; i++){
            result += right._poly[i];
        }
        return result;
    }
    //right is not an empty poly
    else {
        Poly result(right);
        return result;
    }
}
Poly& Poly::operator +=(const Poly& right){
    *this = *this + right;
    return *this;
}
Poly Poly::operator -() const{
    Term neg(-1,0);     //make a term -1^0
    Poly result(*this);
    result *= neg;
    return result;
}
Poly operator -(const Poly& left, const Poly& right){
    Poly result(left);
    result = left + (-right);
    return result;
}
Poly& Poly::operator -=(const Poly& right){
    *this = *this - right;
    return *this;
}

Poly operator * (const Poly& left, const Poly& right){
    Poly polyMultiplyTerm;
    Poly result;
    for(int i=0; i<=right._order; i++){
        //multiply left poly with each term of right
        polyMultiplyTerm = left * right._poly[i];
        result+=polyMultiplyTerm;
    }
    return result;
}
Poly& Poly::operator *=(const Poly& right){
    *this = *this * right;
    return *this;
}
Poly operator / (const Poly& left, const Poly& right){
    assert(right._order>0);

    Term resultT;                       //result of term
    Term divisor = right[right._order]; //first term of right.
    Term dividend = left[left._order];  //first term of left
    Poly PtoSubtract = left;
    Poly resultP;
    const bool debug = false;

    if(left._order < right._order){
        Poly p;
        return p;
    }
    if(debug){
        cout<<"dividen: "<<dividend<<endl;
        cout<<"dividen exp: "<<dividend._exp<<endl;
        cout<<"divisor exp: "<<divisor._exp<<endl;

    }
    for(int i = left._order - right._order;i >=0;i--){
        if(debug){
            cout<<"dividen: "<<dividend<<endl;
            cout<<"dividen exp: "<<dividend._exp<<endl;
            cout<<"divisor exp: "<<divisor._exp<<endl;

        }
        if((dividend < divisor)){
            break;
        }
        //result of term
        resultT = dividend/divisor;
        if(debug){
            cout<<"resultT: "<<resultT<<"["<<dividend<<" / "<<divisor<<"]"<<endl;
        }
        //result of poly + result of term
        resultP += resultT;
        if(debug){
            cout<<"resultP: "<<resultP<<endl;
        }
        //temp poly = multiplication with right and dividend/divisor
        Poly tempP = right * resultT;
        if(debug){
            cout<<"tempP: "<<tempP<<"["<<right<<" * "<<resultT<<"]"<<endl;
        }
        //get a new dividend
        PtoSubtract -= tempP;
        PtoSubtract.fix_order();
        if(debug){
            cout<<"PtoSubtract: "<<PtoSubtract<<"["<<left<<" - "<<tempP<<"]"<<endl;
        }
        dividend = PtoSubtract[PtoSubtract._order];
        if(debug){
            cout<<"dividen: "<<dividend<<endl;
            cout<<"dividen exp: "<<dividend._exp<<endl;
            cout<<"divisor exp: "<<divisor._exp<<endl;
        }
    }
    if(debug){
        cout<<"********************************"<<endl;
    }
    return resultP;
}
Poly& Poly::operator /=(const Poly& right){
    *this = *this / right;
    return *this;
}
void Poly::fix_order(){
    node<Term>* walker =this->_poly.Begin();
    int count = 0;
    // until coef of item is not zero
    while(walker->_item._coef == 0.0){
        if(count != _order){
            //delete walkers except last term
            this->_poly.Delete(walker);
            walker = walker->_next;
        }
        else{
            //saving last zero terms
            break;
        }
        count++;
    }
    //give a new order
    _order -= count;


}




#endif // POLY_H
