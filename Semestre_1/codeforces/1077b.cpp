#include <iostream>
using namespace std;
 
int main(){
    int n, cont = 0, *vet;
    cin >> n;
    vet = new int[n];
    for ( int i = 0 ; i < n ; ++i ){
        cin >> vet[i];
    }
    for ( int i = 1 ; i < n - 1 ; ++i ){
        if(!vet[i] && vet[i-1] && vet[i+1]){
            vet[i+1] = 0;
            cont++;
        }
    }
    cout << cont << endl; 
    delete [] vet;
    return 0;
}