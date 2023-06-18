#ifndef FECHOCONVEXO_HPP
#define FECHOCONVEXO_HPP

#include <iostream>
#include<bits/stdc++.h>
#include "Pilha.hpp"
#include "Ponto.hpp"
#include "FechoConvexo.hpp"

class FechoConvexo{
protected:
    Ponto *pontos;
    int tamanho;
    
    //Preenche o vetor de pontos com os pontos do arquivo
    void Preenche(std::string nome_arquivo);
    
    //Adiciona o angulo da reta formada por p1 e pn
    void Coeficientes(Ponto* p1);

    //Ve se a curva entre p1, p2 e p3 é esquerda, direita ou se são colineares
    //Retorna  maior 0 se for esquerda, menor que 0 se for direita e 0 se forem colineares
    float Orientacao(Ponto p1, Ponto p2, Ponto p3);

    //Troca dois pontos de lugar
    void Troca(Ponto* p1, Ponto* p2);

    //Calcula a distancia euclidiana entre dois pontos
    float dist_eucl(Ponto p1, Ponto p2);

    //Dado que o vetor pontos está ordenado pelo coeficiente angular, remove os pontos colineares
    void RemoveColineares();

public:
    FechoConvexo(std::string nome_arquivo);
    virtual ~FechoConvexo();
    //Resolve o fecho convexo e armazena no vetor pontos
    virtual void Resolve(std::string metodo){};
    //Calcula o tempo gasto em segundos para executar o metodo passado como parametro
    float Tempo(std::string metodo);
    //Printa os pontos do fecho convexo
    void ImprimePontos();
    //Printa as retas que formam o fecho convexo
    void ImprimeRetas();
};

#endif