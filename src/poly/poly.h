#ifndef POLY_H
#define POLY_H
#include "../../../!include/term/term.h"


class Poly
{

public:
    Poly();
    Poly(int order);
    Poly(double* coefs, int order);

    //the BIG 3
    Poly(const Poly& other);
    Poly& operator =(const Poly& rhs);
    ~Poly();

    friend bool operator ==(const Poly& lhs, const Poly& rhs);
    friend bool operator !=(const Poly& lhs, const Poly& rhs);
    friend bool operator >(const Poly& lhs, const Poly& rhs);
    friend bool operator <(const Poly& lhs, const Poly& rhs);

    Term operator[](int order) const;   //return coef at the order

    friend Poly operator +(const Poly& lhs, const Term& t);
    friend Poly operator +(const Poly& lhs, const Poly& rhs);

    friend Poly operator -(const Poly& p);
    friend Poly operator - (const Poly& lhs, const Poly& rhs);

    friend Poly operator *(const Poly& lhs, const Term& t);
    friend Poly operator *(const Poly& lhs, const Poly& rhs);

    friend Poly operator /(const Poly& lhs, const Poly& rhs);
    friend Poly operator %(const Poly& lhs, const Poly& rhs);

    friend ostream& operator <<(ostream& outs, const Poly& p);
    friend istream& operator >>(istream& ins, Poly& p);

    int order() const {return _order;}

private:
    void fix_order();           //get rid of highest terms with zero coefs
    int _order;
    double* _coefs;
};

#endif // POLY_H
