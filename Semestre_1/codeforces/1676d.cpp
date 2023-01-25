#include <iostream>
using llu = long long unsigned int;
using namespace std;
 
int main(){
    llu c, r, tests, max_sum, **vet, soma_aux = 0;
    cin >> tests;
    while(tests){
        cin >> c >> r;
        vet = new llu*[r];
        for (int i = 0 ;  i < r ; i++){ // cria e preenche a matriz
            vet[i] = new llu[r];
            for(int j = 0 ;  j < c ; j++)
                cin >> vet[i][j];
        }
        for (int i = 0; i < r ; i++){ // pega os valores da diagonal principal 
            for (int j = 0; j < r ; j++){
                if (i == 0 || i == l - 1){
                    for (int z = i, y = j; i < r ; z++){


                    }
                }
            }
        }
        soma_aux += soma_diag;
        cout << soma_diag << '\n';
        /*for (int i = 0 ; i < size ; ++i){
            if (i % r == 0 && i != 0)
                cout << '\n';
            cout << vet[i] << ' ';
        }*/
        tests--;
    }
    return 0;
}