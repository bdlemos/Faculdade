#ifndef PILHA
#define PILHA

template <typename T>
class Pilha {
private:
    struct celula {
        T val;
        celula *prev;
        celula(T v, celula *p) : val(v), prev(p) {}
        ~celula() {}
    };
    celula *topo;
    int tamanho;

public:
    Pilha() : topo(nullptr), tamanho(0) {}
    ~Pilha() {
        DestroiPilha();
    }

    void CriaPilha() {
        DestroiPilha();
        topo = new celula(T(), nullptr);
        tamanho = 0;
    }

    bool PilhaVazia(){
        return tamanho == 0;
    }

    void Empilha(T x) {
        celula* novo = new celula(x, topo);
        topo = novo;
        tamanho++;
    }

    T Topo() {
        if (PilhaVazia())
            throw "Pilha está vazia!";

        return topo->val;
    }
    
    T QuaseTopo() {
        if (PilhaVazia())
            throw "Pilha está vazia!";
        T aux = Desempilha();
        T retorno = Topo();
        Empilha(aux);
        return retorno;
    }

    T Desempilha() {
        if (PilhaVazia())
            throw "Pilha está vazia!";

        T ret = topo->val;
        celula *aux = topo;
        topo = topo->prev;
        delete aux;
        tamanho--;
        return ret;
    }

    void DestroiPilha() {
        while (!PilhaVazia()) {
            celula *aux = topo;
            topo = topo->prev;
            delete aux;
            tamanho--;
        }
    }

    int getTamanho() const {
        return tamanho;
    }
};
#endif
