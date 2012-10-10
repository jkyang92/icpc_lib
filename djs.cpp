
#include <cstdlib>

using namespace std;

//the second template is an optional template that allows
//separate disjoint sets that are typesafe between eachother
template <class V,int id=0>
struct djs_node{
    V val;
    djs_node<V,id>* parent;
    int rank;
    explicit djs_node(const V& v) : val(v),parent(NULL), rank(0){}
};

template <class V,int id>
djs_node<V,id> *djs_find(djs_node<V,id>* a){
    if(a==NULL) return NULL;
    if(a->parent) return a->parent = djs_find(a->parent);
    return a;
}

template <class V,int id>
djs_node<V,id> *djs_join(djs_node<V,id>* a,djs_node<V,id>* b){
    if(a==NULL) return b;
    if(b==NULL) return a;
    a = djs_find(a);
    b = djs_find(b);
    if(a==b) return a;
    if(a->rank<b->rank) return a->parent = b;
    b->parent = a;
    if(a->rank==b->rank) a->rank++;
    return a;
}

template <class V,int id>
bool  djs_eq(djs_node<V,id>* a,djs_node<V,id>* b){
    return djs_find(a)==djs_find(b);
}
