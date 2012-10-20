
#include <cassert>
#include <stdexcept>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

template<typename T>
T abs(T a){ return a<0 ? -a : a;}
ull gcd(ull a, ull b){ return a==0 ? b : gcd(b%a,a); }
ull lcm(ull a, ull b){ return (a/gcd(a,b))*b; }

void mult_array(ull a, ull b, ull *out){
#define LOW_MASK (0xFFFFFFFFULL)
#define HIGH_SHIFT (32)
    ull temp = (a&LOW_MASK)*(b&LOW_MASK);
    out[0]+=temp;
    temp = (a&LOW_MASK)*(b>>HIGH_SHIFT);
    //note we have to split this, since two values will go into the 1 and 2
    //slots, and thus overflow might happen
    out[1]+=temp&LOW_MASK;
    out[2]+=temp>>HIGH_SHIFT;
    temp = (a>>HIGH_SHIFT)*(b&LOW_MASK);
    out[1]+=temp&LOW_MASK;
    out[2]+=temp>>HIGH_SHIFT;
    temp = (a>>HIGH_SHIFT)*(b>>HIGH_SHIFT);
    out[2]+=temp&LOW_MASK;
    out[3]+=temp>>HIGH_SHIFT;
    for(int i=0;i<3;i++){
        out[i+1]+=out[i]>>HIGH_SHIFT;
        out[i]&=LOW_MASK;
    }
#undef HIGH_SHIFT
#undef LOW_MASK
}

class rational{
private:
    bool sign;
    ull a,b;
    void reduce(){
        ull g = gcd(a,b);
        if(a!=0){
            a/=g;
            b/=g;
        }
        else{
            assert(b!=0);//if we get this, we've failed horribly
            a=0;
            b=1;
            sign = false;
        }
    }
    friend bool operator==(const rational&,const rational&);
    friend bool operator!=(const rational&,const rational&);
    friend bool operator<(const rational&,const rational&);
    friend bool operator<=(const rational&,const rational&);
    friend bool operator>=(const rational&,const rational&);
    friend bool operator>(const rational&,const rational&);
public:
    rational():sign(false),a(0),b(1){}
    rational(ll val):sign(val<0),a(abs(val)),b(1){}
    rational(int val):sign(val<0),a(abs(val)),b(1){}


    rational& operator+=(const rational& other){
        //this simplifies some later cases
        if(*this==-other || (*this==0 && other==0)){
            sign = false;
            a=0;
            b=1;
            return *this;
        }
        ull d = lcm(b,other.b);
        ull a1 = a*(d/b);
        ull a2 = other.a*(d/other.b);
        b=d;
        if(sign==other.sign){
            a=a1+a2;
        }
        else if(a2>a1){
            a=a2-a1;
            sign=!sign;
        }
        else{
            a=a1-a2;//sign is unchanged
        }
        reduce();
        return *this;
    }
    rational operator+() const{return *this;}
    rational operator-() const{
        rational ret(*this);
        ret.sign = !ret.sign;
        return ret;
    }
    rational& operator-=(const rational& other){return *this+=(-other);}
    rational& operator*=(const rational& other){
        ull g1 = gcd(a,other.b);
        ull g2 = gcd(b,other.a);
        sign = (sign==other.sign);
        a=(a/g1)*(other.a/g2);
        b=(b/g2)*(other.b/g1);
        return *this;
    }
    rational& operator/=(const rational& other){
        if(other==0)
            throw domain_error("divide by zero in rational");
        rational helper = other;
        helper.a=other.b;
        helper.b=other.a;
        return (*this)*=helper;
    }

    ull denominator() const{return b;}
    ull numerator() const{return a;}
};

bool operator==(const rational& r,const rational& s) {return r.sign==s.sign && r.a==s.a && r.b==s.b;}
bool operator<(const rational& r, const rational& s){
    if(r==s) return false;
    if(r.sign){
        if(!s.sign) return true;
        return -s<-r;
    }
    if(s.sign) return false;
    if(r==0) return true;//we know that s!=0 since r!=s
    if(s==0) return false;
    //try to do it directly
    //r.a s.b < r.b s.a
    ull left_array[4]={0,0,0,0};
    ull right_array[4]={0,0,0,0};
    mult_array(r.a,s.b,left_array);
    mult_array(r.b,s.a,right_array);
    for(int i=3;i>=0;i--){
        if(left_array[i]!=right_array[i])
            return left_array[i]<right_array[i];
    }
    return false;//shouldn't happen
}

rational operator+(const rational& r,const rational& s) {return rational(r)+=s;}
rational operator-(const rational& r,const rational& s) {return rational(r)-=s;}
rational operator*(const rational& r,const rational& s) {return rational(r)*=s;}
rational operator/(const rational& r,const rational& s) {return rational(r)/=s;}
bool operator<=(const rational& r,const rational& s){ return !(s<r);}
bool operator>=(const rational& r,const rational& s){ return !(r<s);}
bool operator>(const rational& r,const rational& s){ return s<r;}
bool operator!=(const rational& r,const rational& s){ return !(r==s);}

ll floor(const rational& r){
    //the equals part is important, otherwise, weird things happen with 0
    if(r>=0) return r.numerator()/r.denominator();
    else return -((r.numerator()-1)/r.denominator()+1);
}
ll ceil(const rational& r){
    if(r<0) return (r.numerator()-1)/r.denominator()+1;
    else return -(r.numerator()/r.denominator());
}
double to_double(const rational& r){
    return (r<0 ? -1 : 1)*((double)r.numerator())/r.denominator();//Accuracy?
}
