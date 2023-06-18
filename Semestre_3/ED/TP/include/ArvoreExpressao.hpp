#include "Arvore.hpp"
#include "Pilha.hpp"
#include "FilaEncadeada.hpp"
#include <sstream>
#include <iostream>


class ArvoreExpressao{
    private:
        Arvore expression;
        /**
         * @brief Retorna verdadeiro caso a expressão esteja no formato infixa e falso caso contrário,
         * caso a expressão nao seja válida, lança uma exceçao.
         * 
         * @param s 
         * @return true 
         * @return false 
         */
        bool IsInfix(std::string s);
        /**
         * @brief Transforma do formato infixa para posfixa
         * 
         * @param s 
         * @return std::string 
         */
        std::string In2Pos(std::string s);
    public:
        ArvoreExpressao();
        /**
         * @brief Recebe uma expressão em forma de string e armazena na árvore caso seja válida,
         * caso seja invalida lança um exceçao.
         * 
         * @param s 
         */
        ~ArvoreExpressao();
        /**
         * @brief Recebe uma expressão em forma de string e armazena na árvore caso seja válida,
         * caso seja invalida lança um exceçao.
         * 
         * @param s 
         */
        void InserirExp(std::string s, std::string tipo);
        /**
         * @brief Retorna verdadeiro se nao ouver alguma expressão armazenada
         * 
         * @return true 
         * @return false 
         */
        bool Vazia();
        /**
         * @brief Imprime o valor da expressão
         * 
         */
        void Resultado();
        /**
         * @brief Imprime a expressão na forma infixa
         * 
         */
        void Infixa();
        /**
         * @brief Imprime a expressão na forma posfixa
         * 
         */
        void PosFixa();
};
