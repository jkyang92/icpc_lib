//#include "vect.cpp"
#include "gram_schmidt.cpp"
#include "vect_util.cpp"
#include <vector>

template<typename T,int n>
vect<T,n> orth_proj(const vect<T,n>& a, const vect<T,n>& b){
    return a-proj(a,b);
}

//it's assumed that everything is a basis
template<typename T,int n>
vector<vect<T,n> > intersect_subspaces(vector<vect<T,n> >A, vector<vect<T,n> > B){
    //calculate both perp spaces, then the A\cap B is the perp space of the
    //sum of the perp spaces
    vector<vect<T,n> > perpA,perpB;
    for(int i=0;i<n;i++){
        vect<T,n> temp1,temp2;
        temp1[i]=1;
        temp2[i]=1;
        for(int j=0;j<A.size();j++)
            temp1 = orth_proj(temp1,A[j]);
        for(int j=0;j<B.size();j++)
            temp2 = orth_proj(temp2,B[j]);
        perpA.push_back(temp1);
        perpB.push_back(temp2);
        if(!gram_schmidt(perpA,perpA.size(),false))
            perpA.pop_back();
        if(!gram_schmidt(perpB,perpB.size(),false))
            perpB.pop_back();
    }
    for(int i=0;i<perpB.size();i++){
        perpA.push_back(perpB[i]);
        if(!gram_schmidt(perpA,perpA.size(),false))
            perpA.pop_back();
    }
    vector<vect<T,n> >ret;
    for(int i=0;i<n;i++){
        vect<T,n> temp;
        temp[i]=1;
        for(int j=0;j<perpA.size();j++)
            temp = orth_proj(temp,perpA[j]);
        ret.push_back(temp);
        if(!gram_schmidt(ret,ret.size(),false))
            ret.pop_back();
    }
    return ret;
}
