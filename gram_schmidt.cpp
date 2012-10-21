
#include "vect.cpp"
#include <cmath>
#include <cassert>
#include <vector>

//project a onto b
template<typename T,int d>
vect<T,d> proj(vect<T,d> a,vect<T,d> b){
    return ((a*b)/(b*b))*b;
}

#ifndef EPSILON
#define EPSILON 1e-10
#endif

//works in place
//returns false if the set is not linearly independent
template<typename T,int d>
bool gram_schmidt(std::vector<vect<T,d> >& vects,int nvects,bool normalize){
    for(int i=0;i<nvects;i++){
        vect<T,d> curr = vects[i];
        for(int j=0;j<i;j++) vects[i]-=proj(curr,vects[j]);
        //if we get the zero vector
        if(vects[i].norm()<EPSILON) return false;
    }
    if(normalize)
        for(int i=0;i<nvects;i++)
            vects[i]/=sqrt(vects[i].norm());
    return true;
}
