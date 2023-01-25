#ifndef INDEXACAO_H_
#define INDEXACAO_H_

#include <bits/stdc++.h>
#include <fstream>
#include <dirent.h>

using std::vector;
using std::fstream;
using std::map;
using std::set;
using std::string;
using std::multimap;

class Indexacao{
    private:

        map<string,set<string>> IndiceInvertido_;
        map<string,set<string>> PalavrasBuscadas_;
        multimap<int,string> Matches_;

    public:

        Indexacao();

        /**
         * @brief Lê todos os arquivos de um diretorio e os armazena no indíce invertido
         * 
         * @param diretorio Endereco do diretório a ser lido 
         */
        void adicionar(string diretorio);

        /**
         * @brief Normaliza uma string
         * 
         * @param palavra String a ser normalizada
         * @return String normalizada
         */
        string normalizar(string palavra);

        /**
         * @brief Armazena a quantidade de matches em cada arquivo, dado um conjunto de palavras
         * 
         * @param palavra Vetor de palavras a serem buscadas
        */
        multimap<int,string> buscar(vector<string> palavra);

        /**
         * @brief Imprime a saída da busca
        */
        void imprimir();

        set<string> busca_simples(string palavra);


        /**
         * @brief Retorna o tamanho do indice invertido
        */
        int tamanho();


        /**
         * @brief Retorna o indice invertido
        */
        map<string,set<string>> IndiceInvertido();

        ~Indexacao();
};


#endif