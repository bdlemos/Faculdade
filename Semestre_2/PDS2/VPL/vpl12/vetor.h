#ifndef VETOR_H_
#define VETOR_H_

#include <string>

using std::string;

// Define um vetor de std::string cujos índices variam em
// qualquer intervalo, inclusive negativos.

struct IntervaloVazio{
  int inicio; // Índice de início do vetor que lançou a excecao.
  int fim;    // Índice de fim do vetor que lançou a excecao.
};
struct IndiceInvalido{
  int inicio; // Índice de início do vetor que lançou a excecao.
  int fim;    // Índice de fim do vetor que lançou a excecao.
  int indice; // Índice inválido.
};
struct IndiceNaoInicializado{
  int indice; // Índice do vetor que não foi inicializado.
};

class Vetor {
  public:
    // Cria um vetor cujos índices variam de 'inicio' até 'fim'.
    // PRECONDIÇÃO: fim >= inicio.
    Vetor(int inicio, int fim);

    // Altera o valor do índice i.
    // PRECONDIÇÃO: i está dentro do intervalo de índices do vetor.
    void atribuir(int i, std::string valor);

    // Retorna o valor do índice i.
    // PRECONDIÇÕES: 
    // (1) i está dentro do intervalo de índices do vetor.
    // (2) i foi inicializando anteriormente.
    string valor(int i) const; 

    // Desaloca a memória reservada para os elementos do vetor.
    ~Vetor();
    
  private:
    int inicio_;  // Primeiro índice válido do vetor.
    int fim_;
    string* elementos_;  // Elementos do vetor.
    bool* inicializadas_;
};

#endif