#include "poly.h"
#include "../../../!include/array/array.h"
#include "../../../!include/term/term.h"

Poly::Poly()
{
    _order = 0;
    _coefs = allocate<double>(_order);
    _coefs[0] = 0;
}
Poly::Poly(int order){
    _order = order;
    _coefs = allocate<double>(_order);
    //initialize all coefs as 0
    initialize_array<double>(_coefs,_order+1);
}
Poly::Poly(double* coefs, int order){
    _order = order;
    _coefs = allocate<double>(order);
    //copy coefs to the _coefs
    copy_without_resize<double>(_coefs,coefs,order+1);
}
Poly::Poly(const Poly& other){
    _coefs = allocate<double>(other._order);
    _order = other._order;
    _coefs = copy_with_resize<double>(other._coefs,other._order+1);
}
Poly& Poly::operator =(const Poly& rhs){
    if(this == &rhs){
        return *this;
    }
    delete [] _coefs;
    _order = rhs._order;
    _coefs = allocate<double>(rhs._order);
    copy_without_resize(_coefs,rhs._coefs,rhs._order+1);
    return *this;
}
Poly::~Poly(){
    //destructor
    delete [] _coefs;
}
Term Poly::operator[](int order) const{
    //return term at order
    Term t(_coefs[order],order);
    return t;
}
bool operator ==(const Poly& lhs, const Poly& rhs){
    //their exponents are the same
    if(lhs._order == rhs._order){
        for(int i = lhs._order; i>=0; i--){
            //compare each terms
            Term lhsT = lhs[i];
            Term rhsT = rhs[i];
            if(lhsT != rhsT){
                return false;
            }
        }
    }
    else {
        return false;
    }
    return true;
}
bool operator !=(const Poly& lhs, const Poly& rhs){
    if(lhs._order == rhs._order){
        for(int i = lhs._order; i>=0; i--){
            Term lhsT = lhs[i];
            Term rhsT = rhs[i];
            if(lhsT != rhsT){
                return true;
            }
        }
    }
    else {
        return true;
    }
    return false;


}
bool operator >(const Poly& lhs, const Poly& rhs){
    const bool debug = false;
    //if their exponents are the same
    if(lhs._order == rhs._order){
        for(int i = lhs._order; i>=0; i--){
            if(lhs[i] < rhs[i]){
                if(debug){
                    cout<<"lhs[i]"<<lhs[i]<<endl;
                    cout<<"rhs[i]"<<rhs[i]<<endl;
                }
                return false;
            }
            else if(lhs[i] > rhs[i]){
                if(debug){
                    cout<<"lhs[i]"<<lhs[i]<<endl;
                    cout<<"rhs[i]"<<rhs[i]<<endl;
                }
                return true;
            }
        }
        return true;
    }
    else if(lhs._order > rhs._order){
        for(int i=lhs._order; i>rhs._order; i--){
            //lhs's exp is bigger than rhs's and
            //it has a value with bigger than 0
            if(lhs[i]._coef > 0){
                return true;
            }
        }
        for(int i = rhs._order; i>=0; i--){
            if(lhs[i] < rhs[i]){
                if(debug){
                    cout<<"lhs[i]"<<lhs[i]<<endl;
                    cout<<"rhs[i]"<<rhs[i]<<endl;
                }
                return false;
            }
            else if(lhs[i] > rhs[i]){
                if(debug){
                    cout<<"lhs[i]"<<lhs[i]<<endl;
                    cout<<"rhs[i]"<<rhs[i]<<endl;
                }
                return true;
            }
        }
        return true;
    }

    else{
        for(int i=rhs._order; i>lhs._order; i--){
            //rhs's exp is bigger than lhs's and
            //it has a value with bigger than 0
            if(rhs[i]._coef > 0){
                return false;
            }
        }
        for(int i = lhs._order; i>=0; i--){
            if(lhs[i] < rhs[i]){
                if(debug){
                    cout<<"lhs[i]"<<lhs[i]<<endl;
                    cout<<"rhs[i]"<<rhs[i]<<endl;
                }
                return false;
            }
            else if(lhs[i] > rhs[i]){
                if(debug){
                    cout<<"lhs[i]"<<lhs[i]<<endl;
                    cout<<"rhs[i]"<<rhs[i]<<endl;
                }
                return true;
            }
        }
        return true;
    }
}
bool operator <(const Poly& lhs, const Poly& rhs){
    const bool debug = true;

    if(lhs._order == rhs._order){
        for(int i = lhs._order; i>=0; i--){
            if(lhs[i] > rhs[i]){
                if(debug){
                    cout<<"lhs[i]"<<lhs[i]<<endl;
                    cout<<"rhs[i]"<<rhs[i]<<endl;
                }
                return false;
            }
            else if(lhs[i] < rhs[i]){
                if(debug){
                    cout<<"lhs[i]"<<lhs[i]<<endl;
                    cout<<"rhs[i]"<<rhs[i]<<endl;
                }
                return true;
            }
        }
        return false;
    }
    else if(lhs._order > rhs._order){
        for(int i=lhs._order; i>rhs._order; i--){
            if(lhs[i]._coef > 0){
                return false;
            }
        }
        for(int i = rhs._order-1; i>=0; i--){
            if(lhs[i] > rhs[i]){
                if(debug){
                    cout<<"lhs[i]"<<lhs[i]<<endl;
                    cout<<"rhs[i]"<<rhs[i]<<endl;
                }
                return false;
            }
            else if(lhs[i] < rhs[i]){
                if(debug){
                    cout<<"lhs[i]"<<lhs[i]<<endl;
                    cout<<"rhs[i]"<<rhs[i]<<endl;
                }
                return true;
            }
        }
        return false;

    }
    else{
        for(int i=rhs._order; i>lhs._order; i--){
            if(rhs[i]._coef > 0){
                return true;
            }
        }
        for(int i = lhs._order; i>=0; i--){
            if(lhs[i] < rhs[i]){
                if(debug){
                    cout<<"lhs[i]"<<lhs[i]<<endl;
                    cout<<"rhs[i]"<<rhs[i]<<endl;
                }
                return true;
            }
            else if(lhs[i] > rhs[i]){
                if(debug){
                    cout<<"lhs[i]"<<lhs[i]<<endl;
                    cout<<"rhs[i]"<<rhs[i]<<endl;
                }
                return false;
            }
        }
        return false;
    }
}
Poly operator +(const Poly& lhs, const Term& t){
    if((lhs._order) >= t._exp){
        //copy lhs to poly
        Poly poly(lhs._coefs,lhs._order);
        //add two coefs at t._exp
        poly._coefs[t._exp] += t._coef;
        return poly;
    }
    else{
        //allocate t._exp space to poly
        Poly poly(t._exp);
        //copy lhs's coefs to the poly
        copy_without_resize(poly._coefs,lhs._coefs,lhs._order+1);
        //add two coefs at t._exp
        poly._coefs[t._exp] += t._coef;
        return poly;
    }
}
Poly operator +(const Poly& lhs, const Poly& rhs){
    //copy lhs to the poly
    Poly poly(lhs);
    for(int i = rhs._order; i>=0; i--){
        //adding each terms of rhs to poly
        poly = poly + rhs[i];
    }
    return poly;
}

Poly operator -(const Poly& p){
    //copy p to the poly
    Poly poly(p);
    if(poly._order != 0){
        double* walker = poly._coefs;
        for(int i = p._order; i>=0; i--){
            *walker = -1 * (*walker);   //multiply -1 to each value
            walker++;
        }
    }
    return poly;
}
Poly operator - (const Poly& lhs, const Poly& rhs){
    Poly neg_rhs = -rhs;
    Poly result;
    //adding each terms of neg_rhs to result
    result = lhs + neg_rhs;
    //fix order with higher order terms having zero coeficients
    result.fix_order();
    return result;

}


Poly operator *(const Poly& lhs, const Term& t){
    Poly poly(lhs._order + t._exp);
    for(int i = lhs._order; i>=0; i--){
        //put value of multiplication to the
        //coef of orders with i+t._exp
        poly._coefs[i + t._exp] = lhs._coefs[i] * t._coef;
    }
    return poly;
}
Poly operator *(const Poly& lhs, const Poly& rhs){
    const bool debug = false;
    Poly result;
    //multiply each term of rhs to poly
    for(int i = 0; i<= rhs._order; i++){
        Poly poly;
        poly = (lhs * rhs[i]);
        if (debug){
            cout<<endl<<"poly: "<<poly<<endl<<endl;
            cout<<"result: "<<result<<endl<<endl;
            cout<<"result (["<<result<<"]";
        }
        result = (result + poly);
        if (debug){
            cout<<"+["<<poly<<"]): "<<result<<endl<<endl;
        }
    }
    return result;
}
Poly operator /(const Poly& lhs, const Poly& rhs){

    Term resultT;                   //result of term
    Term divisor = rhs[rhs._order]; //first term of rhs.
    Term dividend = lhs[lhs._order];//first term of lhs
    Poly PtoSubtract = lhs;
    const bool debug = false;

    //when division cannot be done
    if(lhs.order() < rhs.order()|| rhs == 0 || lhs == 0){
        Poly p;
        return p;

    }

    else{
        int order = lhs._order - rhs._order;
        Poly resultP(order);   //allocate space of order+1
        if(debug){
            cout<<endl<<endl<<"******** inside of / ***********"<<endl<<endl;
        }
        for(int i = lhs._order - rhs._order;i >=0;i--){
            if(debug){
                cout<<"dividen: "<<dividend<<endl;
                cout<<"dividen exp: "<<dividend._exp<<endl;
                cout<<"divisor exp: "<<divisor._exp<<endl;

            }
            //result of term
            resultT = dividend/divisor;
            if(debug){
                cout<<"resultT: "<<resultT<<"["<<dividend<<" / "<<divisor<<"]"<<endl;
            }
            //result of poly + result of term
            resultP = resultP + resultT;
            if(debug){
                cout<<"resultP: "<<resultP<<endl;
            }
            //temp poly = multiplication with rhs and dividend/divisor
            Poly tempP = rhs * resultT;
            if(debug){
                cout<<"tempP: "<<tempP<<"["<<rhs<<" * "<<resultT<<"]"<<endl;
            }
            //get a new dividend
            PtoSubtract = PtoSubtract - tempP;
            PtoSubtract.fix_order();
            if(debug){
                cout<<"PtoSubtract: "<<PtoSubtract<<"["<<lhs<<" - "<<tempP<<"]"<<endl;
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
}
Poly operator %(const Poly& lhs, const Poly& rhs){
    //using rhs*remainder = lhs
    Poly div = lhs / rhs;
    return lhs - div * rhs;

}
istream& operator >>(istream& ins, Poly& p){
    Term t;
    Poly newP;
    do{
        ins>>t;
        newP = newP + t;
    }while(t._exp != 0);
    p = newP;
    return ins;
}
ostream& operator <<(ostream& outs, const Poly& p){
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(1);

    for(int i = p._order; i>=0; i--){
        //when coef == 0 && exp == 0
        if (p._coefs[i] == 0.0 && i >= 0) {
            outs<<"";
        }
        else if (p._coefs[i] != 0.0 && i == 0) {
            if(p._coefs[i] > 0){
                outs<<" +"<<p._coefs[i];
            }
            else{
                outs<<" "<<p._coefs[i];
            }
        }
        //coefs with exp 1
        else if (p._coefs[i] != 0.0 && i == 1) {
            if(p._coefs[i] > 0){
                outs<<" +"<<p._coefs[i]<<"X";
            }
            else{
                outs<<" "<<p._coefs[i]<<"X";
            }
        }
        //coefs,exp both have a value with nonzero
        else{
            if(p._coefs[i] > 0){
                outs<<" +"<<p._coefs[i]<<"X^"<<i;
            }
            else{
                outs<<" "<<p._coefs[i]<<"X^"<<i;
            }
        }
    }
    return outs;
}
void Poly::fix_order(){
    //modifies the object and resets the _order to its real value
    int count = 0;
    double* walker = _coefs;
    //sent walker to the end of the _coefs
    walker+= (_order+1);
    //walk down to nonzero value
    do{
        walker--;
        count++;
    }while(*walker == 0.0 && count <= _order);
    //delete order with 0 coefs
    _order = _order - count + 1;
    delete [] _coefs;
    double* new_coefs = copy_with_resize(_coefs,_order+1);
    _coefs = new_coefs;
}






