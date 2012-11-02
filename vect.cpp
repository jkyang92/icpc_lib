#ifndef VECT_CPP_GUARD
#define VECT_CPP_GUARD

#include <numeric>
#include <algorithm>
#include <functional>
using namespace std;
template<typename T,int n>
class vect{
    T val[n];
public:
    //always constructs the zero vector
    vect(){ fill_n(val,n,(T)0); }
    vect(const vect<T,n>& other){ copy(other.val,other.val+n,val);}
    vect<T,n>& operator=(const vect<T,n>& other){
        if(&other==this) return *this;
        copy(other.val,other.val+n,val);
        return *this;
    }
#define V_OP(op)                                                        \
    vect<T,n>& operator op ## =(const vect<T,n>& other){                \
        for(int i=0;i<n;i++) val[i] op ##= other.val[i];                \
        return *this;                                                   \
    }
    V_OP(+);
    V_OP(-);
#undef V_OP
    vect<T,n> operator-() const{
        vect<T,n> ret;
        transform(val,val+n,ret.val,negate<T>());
        return ret;
    }
    //note, this is the length squared norm
    T norm() const{ return (*this)*(*this); }
    bool operator==(const vect<T,n>& other) const{ return equal(val,val+n,other.val); }
    bool operator!=(const vect<T,n>& other) const{ return !(this==other); }
    //dot product
    T operator*(const vect<T,n>& other) const{ return inner_product(val,val+n,other.val,(T)0); }
#define S_OP(op)                                             \
    vect<T,n>& operator op ## =(const T& k){                 \
        for(int i=0;i<n;i++) val[i] op ## = k;               \
        return *this;                                        \
    }
    S_OP(*);
    S_OP(/);
#undef S_OP
    const T& operator[](int index) const { return val[index]; }
    T& operator[](int index){ return val[index]; }
};

#define WRAP(op,t2)                                                     \
    template<typename T,int n>                                          \
    vect<T,n> operator op (const vect<T,n>& a,t2 b){                    \
        vect<T,n> ret (a);                                              \
        return (ret op##= b);                                           \
    }
#define COMMA ,
WRAP(+,const vect<T COMMA n>&)
WRAP(-,const vect<T COMMA n>&)
WRAP(*,const T&)
WRAP(/,const T&)
#undef WRAP
//backwards versions
template<typename T, int n>
vect<T,n> operator*(const T& k, const vect<T,n>& a){ return a*k; }
template<typename T, int n>
vect<T,n> operator/(const T& k, const vect<T,n>& a){ return a/k; }

#endif
