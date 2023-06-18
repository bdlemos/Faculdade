#ifndef FECHOCONVEXOJARVIS_HPP
#define FECHOCONVEXOJARVIS_HPP


#include<bits/stdc++.h>
#include "Pilha.hpp"
#include "Ponto.hpp"
#include "FechoConvexo.hpp"

class Jarvis: public FechoConvexo{
private:
    //Verifica se o ponto q esta no segmento pr
    bool EstaNoSegmento(Ponto p, Ponto q, Ponto r);
public:
    /*Recebe o nome de um arquivo com pontos x y e armazena no vetor pontos. */
    Jarvis(std::string nome_arquivo): FechoConvexo(nome_arquivo){};

    //Resolve o fecho convexo e armazena no vetor pontos
    //O parametro deve ser vazio ""
    void Resolve(std::string metodo);
    ~Jarvis() = default;
};

#endif