#include <iostream>
#include <cstdlib>
#include <ctime>
#include "ArvoreBinaria.hpp"

using namespace std;

int main(){
    Arvore arv;
    for(int i=0 ; i<1000 ; i++)
        arv.Insere(rand()%1000);
    std::cout << "Percurso em pré-ordem: ";
    arv.Caminha(1);
    std::cout << std::endl;

    std::cout << "Percurso em ordem: ";
    arv.Caminha(2);
    std::cout << std::endl;

    std::cout << "Percurso em pós-ordem: ";
    arv.Caminha(3);
    std::cout << std::endl;

    return 0;
}