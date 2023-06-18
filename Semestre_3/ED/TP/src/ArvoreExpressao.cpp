#include "ArvoreExpressao.hpp"

int operatorPriority(std::string x){
    if (x == "+") return 1;
    if (x == "-") return 1;
    if (x == "*") return 2;
    if (x == "/") return 2;
    return 0;
}


ArvoreExpressao::ArvoreExpressao(){}

void ArvoreExpressao::InserirExp(std::string s,std::string tipo){
    std::string saux = s;
    
    if (IsInfix(s) and tipo == "INFIXA") 
        s = In2Pos(s);
    else if ((!IsInfix(s) and tipo == "INFIXA") or (IsInfix(s) and tipo == "POSFIXA"))
        throw EXPINVALIDA{saux};

    std::stringstream ss(s);
    Pilha<std::string> expressao;
    std::string aux;
    while (ss >> aux) expressao.Empilha(aux);
    try{
        while (!expressao.PilhaVazia()) expression.Insere(expressao.Desempilha());
    }catch(EXPINVALIDA e){
        throw EXPINVALIDA{saux};
    }
    expressao.~Pilha();
    if(expression.ExpressaoValida()) std::cout<< "EXPRESSAO OK: " << saux << std::endl;
    else expression.Limpa(), throw EXPINVALIDA{saux};
}

ArvoreExpressao::~ArvoreExpressao(){
    expression.~Arvore();
}

std::string ArvoreExpressao::In2Pos(std::string s){
    Pilha<std::string> operators;
    FilaEncadeada expressao;
    std::string x = "";
    operators.CriaPilha();
    std::string aux;
    std::stringstream ss(s);
    
    while (ss >> aux) expressao.Enfileira(aux);
    while (!expressao.Vazia()){
        std::string caracter = expressao.Desenfileira();
        int operation = operatorPriority(caracter);
        if(operation or caracter == "("){
            if(!operators.PilhaVazia()){
                std::string last = operators.Desempilha();
                if(operation <=operatorPriority(last) and caracter != "(")
                    x += last + " ";
                else
                    operators.Empilha(last);
            }
            operators.Empilha(caracter);
        }else if(!operators.PilhaVazia() and caracter == ")"){
            std::string last = operators.Desempilha();
            while(last != "(") x += last + " ", last = operators.Desempilha();
        }else{
            x += caracter + " ";
        }
    }
    while(!operators.PilhaVazia()) x += operators.Desempilha() + " ";
    operators.~Pilha();
    expressao.~FilaEncadeada();
    return x;
}

void ArvoreExpressao::Infixa(){
    expression.Caminha(2);
}

void ArvoreExpressao::PosFixa(){
    expression.Caminha(3);
}

void ArvoreExpressao::Resultado(){
    expression.Caminha(1);
}

bool ArvoreExpressao::IsInfix(std::string s){
    int n1 = 0, n2 = 0; 
    for (auto &&i : s){
        if(isalpha(i)) throw EXPINVALIDA{s};;
        if(i == '(') n1++;
        else if(i == ')') n2++;
    }
    if(n1 != n2) throw EXPINVALIDA{s};;
    if(n1) return true;
    Pilha<std::string> exp;
    std::string aux;
    std::stringstream ss(s);
    while (ss >> aux) exp.Empilha(aux);

    aux = exp.Desempilha();
    if (aux == "+" or aux == "-" or aux == "*" or aux == "/") return false;
    return true;
}

bool ArvoreExpressao::Vazia(){
    return expression.Vazia();
}