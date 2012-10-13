
#include "vect.cpp"
#include <cmath>
#include <cassert>

//project a onto b
template<typename T,int d>
vect<T,d> proj(vect<T,d> a,vect<T,d> b){
    return ((a*b)/(b*b))*b;
}

//works in place
//returns false if the set is not linearly independent
template<typename T,int d>
bool gram_schmidt(vect<T,d>* vects,int nvects,bool normalize){
    for(int i=0;i<nvects;i++){
        vect<T,d> curr = vects[i];
        for(int j=0;j<i;j++) vects[i]-=proj(curr,vects[j]);
        //if we get the zero vector
        if(vects[i]==vect<T,d>()) return false;
    }
    if(normalize)
        for(int i=0;i<nvects;i++)
            vects[i]/=sqrt(vects[i].norm());
    return true;
}

int main(){
    vect<double,2> vects[2];
    vects[0][0]=1;
    vects[0][1]=0;
    vects[1][0]=1;
    vects[1][1]=1;
    assert(gram_schmidt(vects,2,true));
    assert(vects[1][0]==0);
}
