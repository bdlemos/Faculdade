
#include <iostream>
#include <string>

struct EXPINVALIDA{
  std::string i;
};
struct DIVPOR0{
  std::string i;
};

class node{
    private:
        std::string item;
        node *esq;
        node *dir;

    public:
        node(std::string v) : item(v), esq(nullptr), dir(nullptr){};
        ~node() {}
    friend class Arvore;
};

class Arvore{
    //Essa arvore cresce para a direita
    private:
        node *Raiz;
        void InsereRecursivo(node* &p, std::string item);
        void ApagaRecursivo(node* p);
        float PreOrdem(node* p); // Resultado
        void InOrdem(node* p); // InFixa
        void PosOrdem(node* p); // PosFixa
        /**
         * @brief Ve se é possivel armazenar algum item a partir do nó de entrada
         * 
         * @param p 
         * @return true 
         * @return false 
         */
        bool isValid(node*p);
    public:
        Arvore();
        ~Arvore();
        bool Vazia();
        /**
         * @brief Retorna verdadeiro caso a expressão armazenada seja valida 
         * e falso caso contrario
         */
        bool ExpressaoValida();
        /**
         * @brief Recebe uma string de um único elemento e insere na árvore
         * Lança um erro caso seja uma expressão inválida
         * @param string 
         */
        void Insere(std::string item);
        /**
         * @brief Recebe um valor inteiro em 1, 2 ou 3 e realiza o cominhamento da árvore.
         * 1- Percorre pré ordem, 2- Percorre em ordem, 3- Percorre em pos ordem
         * 
         * @param tipo 
         */
        void Caminha(int tipo);
        /**
         * @brief Limpa a árvore
         * 
         */
        void Limpa();
    };
