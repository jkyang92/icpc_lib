/* For this file, there are things that are critical either to other functions
 * or to having a vector class that makes sense, and other optional but useful
 * utilities and stuff
 */

#include <numeric>
#include <algorithm>
using namespace std;
template<typename T,int n>
class vect{
    T val[n];
public:
    //Begin core functionality
    //always constructs the zero vector
    vect(){
        for(int i=0;i<n;i++) val[i]=0;
    }
    vect(const vect<T,n>& other){
        for(int i=0;i<n;i++) val[i]=other.val[i];
    }
    vect<T,n>& operator=(const vect<T,n>& other){
        for(int i=0;i<n;i++) val[i]=other.val[i];
        return *this;
    }
    vect<T,n>& operator+=(const vect<T,n>& other){
        for(int i=0;i<n;i++) val[i]+=other.val[i];
        return *this;
    }
    vect<T,n> operator+(const vect<T,n>& other) const{
        vect<T,n> ret = *this;
        return ret+=other;
    }
    vect<T,n> operator-() const{
        vect<T,n> ret;
        for(int i=0;i<n;i++) ret.val[i] = -val[i];
        return ret;
    }
    vect<T,n>& operator-=(const vect<T,n>& other){
        for(int i=0;i<n;i++) val[i]-=other.val[i];
        return *this;
    }
    vect<T,n> operator-(const vect<T,n>& other) const{
        vect<T,n> ret = *this;
        return ret-=other;
    }
    //computes the standard norm, i.e. abs squared
    T norm() const{
        return (*this)*(*this);
    }
    bool operator==(const vect<T,n>& other) const{
        for(int i=0;i<n;i++)
            if(val[i]!=other.val[i])
                return false;
        return true;
    }
    bool operator!=(const vect<T,n>& other) const{
        return !(this==other);
    }
    //dot product
    T operator*(const vect<T,n>& other) const{
        return inner_product(val,val+n,other.val,0);
    }
    //scalar product
    vect<T,n>& operator*=(const T& k){
        for(int i=0;i<n;i++) val[i]*=k;
        return *this;
    }
    vect<T,n>& operator/=(const T& k){
        for(int i=0;i<n;i++) val[i]/=k;
        return *this;
    }

    const T& operator[](int index) const { return val[index]; }
    T& operator[](int index){ return val[index]; }

    //BEGIN OPTIONAL FUNCTIONALITY

    //L_infinity norm, or uniform norm
    T infnorm() const{
        T ret = 0;
        for(int i=0;i<n;i++) ret = max(abs(val[i]),ret);
        return ret;
    }
    //L_1 norm, or taxi-cab norm
    T onenorm() const { return accumulate(val,val+n,0); }
};

//Core Global Functions

template<typename T,int n>
vect<T,n> operator*(const vect<T,n>& a, const T& k){
    vect<T,n> ret (a);
    return ret*=k;
}

template<typename T,int n>
vect<T,n> operator/(const vect<T,n>& a, const T& k){
    vect<T,n> ret (a);
    return ret/=k;
}

template<typename T, int n>
vect<T,n> operator*(const T& k, const vect<T,n>& a){
    vect<T,n> ret (a);
    return ret*=k;
}

//Optional Global Functions

template<typename T>
vect<T,3> cross(const vect<T,3>& a, const vect<T,3>& b){
    vect<T,3> ret;
    ret[0] = a[1]*b[2]-a[2]*b[1];
    ret[1] = a[2]*b[0]-a[0]*b[2];
    ret[2] = a[0]*b[1]-a[1]*b[0];
    return ret;
}

template<typename T,int n,int m>
vect<T,n> change_dim(vect<T,m> v){
    vect<T,n> ret;
    for(int i=0;i<min(n,m);i++) ret[i] = v[i];
    return ret;
}
