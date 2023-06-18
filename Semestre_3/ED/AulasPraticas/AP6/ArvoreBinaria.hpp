
#include <iostream>
#include <string>

class node{
    private:
        int item;
        node *esq;
        node *dir;

    public:
        node(int v) : item(v), esq(nullptr), dir(nullptr){};
        ~node() {}
    friend class Arvore;
};

class Arvore{
    //Essa arvore cresce para a direita
    private:
        node *Raiz;
        void InsereRecursivo(node* &p, int item);
        void ApagaRecursivo(node* p);
        void PreOrdem(node* p); // Resultado
        void InOrdem(node* p); // InFixa
        void PosOrdem(node* p); // PosFixa
        /**
         * @brief Ve se é possivel armazenar algum item a partir do nó de entrada
         * 
         * @param p 
         * @return true 
         * @return false 
         */
    public:
        Arvore();
        ~Arvore();
        bool Vazia();
        void Insere(int item);
        void Caminha(int tipo);
        void Limpa();
    };
