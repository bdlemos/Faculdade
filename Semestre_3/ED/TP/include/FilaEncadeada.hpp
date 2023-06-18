#include <iostream>
typedef struct item{
    std::string val;
    item* prox;
} Item;


class FilaEncadeada{
    public:
        FilaEncadeada();
        ~FilaEncadeada();
        void Enfileira(std::string x);
        std::string Desenfileira();
        void Limpa();
        int getTamanho();
        bool Vazia();
    private:
        Item* frente;
        Item* tras;
        int tamanho;
};