#include "vect.cpp"
#include <cstdarg>

using namespace std;

//additional utilities for vect.cpp
template<typename T>
vect<T,3> cross(const vect<T,3>& a, const vect<T,3>& b){
    vect<T,3> ret;
    ret[0] = a[1]*b[2]-a[2]*b[1];
    ret[1] = a[2]*b[0]-a[0]*b[2];
    ret[2] = a[0]*b[1]-a[1]*b[0];
    return ret;
}

template<typename T,int n,int m>
vect<T,n> change_dim(const vect<T,m>& v){
    vect<T,n> ret;
    for(int i=0;i<min(n,m);i++) ret[i] = v[i];
    return ret;
}
template<typename T,int n>
vect<T,n> make_vect(T first,...){
    va_list args;
    vect<T,n> ret;
    ret[0]=first;
    va_start(args,first);
    for(int i=1;i<n;i++)
        ret[i]=va_arg(args,T);
    va_end(args);
    return ret;
}

//project a onto b
template<typename T,int d>
vect<T,d> proj(vect<T,d> a,vect<T,d> b){
    return ((a*b)/(b*b))*b;
}

template<typename T,int n>
vect<T,n> orth_proj(const vect<T,n>& a, const vect<T,n>& b){
    return a-proj(a,b);
}
