typedef struct item{
    int val;
    item* prox;
} Item;


class FilaEncadeada{
    public:
        FilaEncadeada();
        ~FilaEncadeada();
        void Enfileira(int x);
        int Desenfileira();
        void Limpa();
        int getTamanho();
        bool Vazia();
    private:
        Item* frente;
        Item* tras;
        int tamanho;
};