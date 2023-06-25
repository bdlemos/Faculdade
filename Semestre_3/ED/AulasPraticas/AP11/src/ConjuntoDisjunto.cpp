#include "ConjuntoDisjunto.hpp" 

	
ConjuntoDisjunto::ConjuntoDisjunto(){}
ConjuntoDisjunto::~ConjuntoDisjunto(){}

void ConjuntoDisjunto::makeSet(long x){
    node* novo = new node;
    novo->data = x;
    novo->parent = novo;
    novo->rank = 0;
    sets[x] = novo;
}
void ConjuntoDisjunto::unionSet(long x, long y){
    node* ptx = sets[x];
    node* pty = sets[y];
    while(ptx->parent != ptx){
        ptx = ptx->parent;
    }
    while(pty->parent != pty){
        pty = pty->parent;
    }
    if(ptx->rank > pty->rank){
        pty->parent = ptx;
    }else if(ptx->rank < pty->rank){
        ptx->parent = pty;
    }else{
        pty->parent = ptx;
        ptx->rank++;
    }
}
long ConjuntoDisjunto::findSet(long x){
    node* ptx = sets[x];
    while(ptx->parent != ptx){
        ptx = ptx->parent;
    }
    return ptx->data;
}

