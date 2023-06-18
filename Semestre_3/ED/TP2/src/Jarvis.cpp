#include "Jarvis.hpp"

#ifndef Jarvis_CPP
#define Jarvis_CPP

bool Jarvis::EstaNoSegmento(Ponto p, Ponto q, Ponto r) 
{ 
    return (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) && 
            q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y));
       
} 

void Jarvis::Resolve(std::string metodo){
    if (tamanho < 3) throw std::string("Nao e possivel calcular o fecho convexo com menos de 3 pontos");
    // coloca o mais a esquerda na primeira posicao do vetor
    int l = 0;
    for (int i = 1; i < tamanho; i++){
        if (pontos[i].x < pontos[l].x){
            l = i;
        }else if (pontos[i].x == pontos[l].x && 
		         pontos[i].y < pontos[l].y)
		    l = i;
    }
    Pilha<Ponto> pilha;
    int p = l, q;

	do{
        pilha.Empilha(pontos[p]);
		q = (p + 1) % tamanho;
		for (int i = 0; i < tamanho; i++){
            if (Orientacao(pontos[p], pontos[i], pontos[q]) > 0)
                q = i;
            if (p != i && Orientacao(pontos[p], pontos[i], pontos[q]) == 0 && 
			    EstaNoSegmento(pontos[p], pontos[q], pontos[i]))
			    q = i;
		}
		p = q;

	} while (p != l);
    
    delete[] pontos;
    
    tamanho = pilha.getTamanho();
    pontos = new Ponto[tamanho];
    for (int i = 0; i < tamanho; i++) pontos[i] = pilha.Desempilha();
}

#endif