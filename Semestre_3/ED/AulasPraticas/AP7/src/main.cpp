#include <iostream>
#include "Sorts.hpp"

using namespace std;

void preenche_vetor(int *v, int* v2 , int n){
    for (int j = 0; j < n; j++){
        v[j] = rand()%n; 
        v2[j] = v[j];
    }
}

int main(){
    srand(time(NULL));

    Sorts* sorts = new Sorts();

    int size = 1e6;
    int* heap = new int[size];
    int* shell = new int[size];
    double theap = 0, tshell = 0;
    for (int i = 0; i < 10; i++){
        preenche_vetor(heap, shell, size);
        theap += sorts->getTimeHeap(heap, size);
        tshell += sorts->getTimeShell(shell, size);
    }
    cout << "Heap: " << theap/10 << " segundos" << endl;
    cout << "Shell: " << tshell/10 << " segundos" << endl;
    cout << endl;
    delete sorts;
    delete [] heap;
    delete [] shell;
    return 0;
}