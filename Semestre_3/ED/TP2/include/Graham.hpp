#ifndef FECHOCONVEXOGRAHAM_HPP
#define FECHOCONVEXOGRAHAM_HPP


#include<bits/stdc++.h>
#include "Pilha.hpp"
#include "Ponto.hpp"
#include "FechoConvexo.hpp"

class Graham: public FechoConvexo{
private:
    
    //Ordena o vetor de pontos pelo coeficiente angular da posição 0 a n-1
    //Caso o coeficiente seja igual, ordena pelo ponto mais distante do ponto p0
    void mergeSort(Ponto* pontos, Ponto p1, int inicio, int fim);
    void merge(Ponto* pontos, Ponto p1, int inicio, int meio, int fim);
    
    //Ordenada o vetor de pontos pelo coeficiente angular da posição 1 a n-1
    //Caso o coeficiente seja igual, ordena pelo ponto mais distante do ponto p0
    //Passar o vetor de pontos a partir da segunda posição aka &pontos[1] e tamanho -1
    void insertionSort(Ponto* pontos, int tamanho);

    //Ordena o vetor de pontos pelo coeficiente angular da posição 0 a n-1
    //Caso o coeficiente seja igual, ordena pelo ponto mais distante do ponto p0
    //Passar o vetor de pontos a partir da segunda posição aka &pontos[1] e tamanho - 1
    void bucketSort(Ponto* pontos, int tamanho);

    //Ordena usando merge sort
    void Merge();
    
    //Ordena usando insertion sort
    void Insertion();
    
    //Ordena usando bucket sort
    void Linear();
    
public:
    /*Recebe o nome de um arquivo com pontos x y e coloca o 
    ponto com menor y e menor x na primeira posição*/
    Graham(std::string nome_arquivo);

    //Resolve o fecho convexo e armazena no vetor pontos
    //O metodo pode ser Merge, Insertion ou Linear    
    void Resolve(std::string metodo);

    ~Graham() = default;
};

#endif