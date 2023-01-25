#include <bits/stdc++.h>
#include "indexacao.h"

using namespace std;

int main() { 
    bool condicao = true;
    while (condicao){
        system("clear");  
        cout << "Maquina de busca" << endl << endl;
        cout << "Insira o conjunto de palavras a serem buscadas" << endl;
        vector <string> palavras_buscadas;
        string s, aux;
        getline(cin,s);
        for (auto &&i : s){
            if(i != ' ') aux += i;
            else palavras_buscadas.push_back(aux), aux.clear();
        }
        palavras_buscadas.push_back(aux);

        Indexacao busca = Indexacao();
        busca.adicionar("./documentos/");
        busca.buscar(palavras_buscadas);
        cout << endl;
        busca.imprimir();
        cout << endl <<"Deseja realizar mais alguma busca? \nCaso sim, digite 1. Caso contrario, digite 0." << endl;
        cin >> condicao;
        getchar();
    }
    return 0;
}