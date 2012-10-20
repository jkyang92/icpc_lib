#include "vect.cpp"

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
