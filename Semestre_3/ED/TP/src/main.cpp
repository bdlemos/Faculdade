#include <bits/stdc++.h>
#include "ArvoreExpressao.hpp"



int main() {
    std::cout << std::fixed << std::setprecision(6);
    ArvoreExpressao *expressao = new ArvoreExpressao();
    std::string input;

    while(std::getline(std::cin,input)){
        try{
            std::stringstream ss(input);
            std::string option, type;
            // Le a opcao
            ss >> option;
            ss >> type;
            if (option == "LER"){
                std::string aux = "";
                //Monta a expressão no formato de string
                while(ss >> input) aux += input + " ";
                //Esvazia a expressão caso nao esteja vazia
                if(!expressao->Vazia()) expressao->~ArvoreExpressao();
                std::cout << std::endl;
                //Insere na árvore
                expressao->InserirExp(aux,type);
            }else if (!expressao->Vazia()){
                if(option == "INFIXA"){
                    std::cout << "INFIXA: ";
                    expressao->Infixa();
                    std::cout << std::endl;
                }else if (option == "POSFIXA"){
                    std::cout << "POSFIXA: ";
                    expressao->PosFixa();
                    std::cout << std::endl;
                }else if (option == "RESOLVE"){
                    expressao->Resultado();
                    std::cout << std::endl;
                }else{
                    std::cout << "OPCAO INVALIDA" << std::endl;
                }
            }else{
                std::cout << "ERRO: EXP NAO EXISTE" << std::endl;
            }
        }
        catch(EXPINVALIDA e){
            std::cout << "ERRO: " << e.i << " NAO VALIDA" << '\n';
        }
        catch(DIVPOR0 e){
            std::cout << "ERRO: DIVISAO POR ZERO" << '\n';
        }
    }
    delete expressao;
    return 0;
}
