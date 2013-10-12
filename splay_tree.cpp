#include <cassert>
#include <cstddef>

using namespace std;

template<typename T>
struct node{
    T value;//change this to make weird trees
    node<T> *left, *right;
    node<T> *parent;
    node(const T& val) : value(val),left(NULL),right(NULL),parent(NULL){}
    ~node(){
        if(left) delete left;
        if(right) delete right;
    }
};

//this just finds the node
template<typename T>
node<T> *node_find(node<T> *n,const T& val){
    while(n){
        if(n->value<val) n = n->right;
        else if(val<n->value) n = n->left;
        else return n;
    }
    return NULL;
}

template<typename T>
void disconnect_left(node<T> *n){
    if(!n) return;
    if(n->left) n->left->parent = NULL;
    n->left = NULL;
}

template<typename T>
void disconnect_right(node<T> *n){
    if(!n) return;
    if(n->right) n->right->parent = NULL;
    n->right = NULL;
}

template<typename T>
void disconnect_parent(node<T> *n){
    if(!n || !n->parent) return;
    if(n->parent->left == n) disconnect_left(n->parent);
    else disconnect_right(n->parent);
}

template<typename T>
void connect_left(node<T> *n, node<T> *l){
    disconnect_left(n);
    disconnect_parent(l);
    if(n) n->left = l;
    if(l) l->parent = n;
}

template<typename T>
void connect_right(node<T> *n, node<T> *r){
    disconnect_right(n);
    disconnect_parent(r);
    if(n) n->right= r;
    if(r) r->parent = n;
}

template<typename T>
node<T> *node_insert(node<T> *n,const T& val){
    if(!n) return new node<T>(val);
    while(true){//this loop leaks if we are given a bad comparator
        if(n->value<val){
            if(!n->right) connect_right(n,new node<T>(val));
            n = n->right;
        }
        else if(val<n->value){
            if(!n->left) connect_left(n,new node<T>(val));
            n = n->left;
        }
        else return n;
    }
}


template<typename T>
void rotate_left(node<T> *n){
    node<T> *r = n->right;
    node<T> *p = n->parent;
    if(p){
        if(p->right==n) connect_right(p,r);
        else connect_left(p,r);
    }
    connect_right(n,r->left);
    connect_left(r,n);
}


template<typename T>
void rotate_right(node<T> *n){
    node<T> *l = n->left;
    node<T> *p = n->parent;
    if(p){
        if(p->right==n) connect_right(p,l);
        else connect_left(p,l);
    }
    connect_left(n,l->right);
    connect_right(l,n);
}

template<typename T>
void splay_node(node<T> *n){
    if(!n) return;
    while(n->parent){
        if(!n->parent->parent){
            if(n->parent->left==n) rotate_right(n->parent);
            else rotate_left(n->parent);
        }
        else if(n->parent->left == n){
            if(n->parent->parent->left == n->parent){
                rotate_right(n->parent->parent);
                rotate_right(n->parent);
            }
            else{
                rotate_right(n->parent);
                rotate_left(n->parent);
            }
        }
        else if(n->parent->right == n){
            if(n->parent->parent->right == n->parent){
                rotate_left(n->parent->parent);
                rotate_left(n->parent);
            }
            else{
                rotate_left(n->parent);
                rotate_right(n->parent);
            }
        }
    }
}

//note, copying trees shares data, you have to do deep copies manually
template<typename T>
struct tree_set{
    node<T> *root;
    tree_set() : root(NULL) {}
    ~tree_set() {if(root) delete root;}
    node<T> *find(const T& val){
        root = node_find(root,val);
        splay_node(root);
        return root;
    }
    node<T> *insert(const T& val){
        root = node_insert(root,val);
        splay_node(root);
        return root;
    }
    void erase(node<T> *n){
        splay_node(n);
        node<T> *l = n->left;
        node<T> *r = n->right;
        disconnect_left<T>(n);
        disconnect_right<T>(n);
        delete n;
        if(l){
            while(l->right) l = l->right;
            splay_node(l);
            connect_right(l,r);
            root = l;
        }
        else
            root = r;
    }
};
