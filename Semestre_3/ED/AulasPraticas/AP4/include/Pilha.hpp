#include "FilaEncadeada.hpp"

class Pilha{
    private:
        FilaEncadeada* pilha;
    public:
        Pilha();
        ~Pilha();
        void CriaPilha();
        bool PilhaVazia();
        void Empilha(int x);
        int Desempilha();
        void DestroiPilha();
        int getTamanho();

};