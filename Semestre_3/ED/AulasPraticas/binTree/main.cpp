#include <iostream>
#include <cstdlib>
#include <ctime>
#include "ArvoreBinaria.hpp"

using namespace std;

int main(){
    Arvore arv;
    arv.Insere(1);
    arv.Insere(4);
    arv.Insere(3);
    arv.Insere(5);
    arv.Insere(2);
    arv.Insere(2);
    arv.Insere(11);
    arv.Insere(12);
    arv.Insere(20);
    arv.Insere(1);
    arv.Insere(4);
    arv.Insere(9);
    arv.Insere(13);
    arv.Insere(17);
    arv.Insere(25);
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