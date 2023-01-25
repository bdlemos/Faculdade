#include "indexacao.h"

Indexacao::Indexacao(){
    IndiceInvertido_ = map<string,set<string>>();
    PalavrasBuscadas_ = map<string,set<string>>();
    Matches_ = std::multimap<int,string>();
}

void Indexacao::adicionar(string diretorio){
    
    DIR *dir; struct dirent *diread;
    vector<string> files;

    //Armazena os nomes dos arquivos num vector
    if ((dir = opendir(diretorio.c_str())) != nullptr) {
        while ((diread = readdir(dir)) != nullptr) {
            files.push_back(diread->d_name);
        }
        closedir (dir);
    } else {
        perror ("opendir");
        return;
    }

    //Lê todos os arquivos e guarda no indíce invertido
    for (auto file : files) {
        fstream f(diretorio + file);
        string s;
        if ( f.is_open() ) {
            while (f.good()){
                f >> s;
                IndiceInvertido_[normalizar(s)].insert(file);
          }
        }
    }
}

multimap<int,string> Indexacao::buscar(vector<string> palavras_buscadas){

    PalavrasBuscadas_ = map<string,set<string>>();
    Matches_ =  multimap<int,string>();
    map<string, int> Aux_;

    for (auto &&i : palavras_buscadas){
        for (auto &&j : IndiceInvertido_[normalizar(i)]){
            PalavrasBuscadas_[normalizar(i)].insert(j);
        }
    }

    for (auto &&i : PalavrasBuscadas_){
        for (auto &&j : i.second){
            Aux_[j]++;
        }
    }

    for (auto &&i = Aux_.rbegin(); i != Aux_.rend(); i++){
        if (i->second == palavras_buscadas.size())
            Matches_.insert({i->second, i->first});
    }

    return Matches_;
}

void Indexacao:: imprimir(){
    
    if(!Matches_.size()){
        std::cout << "Este conjunto de palavras não está em nenhum arquivo." << std::endl;
        return;
    }

    int item = 1;

    for (auto &&i = Matches_.rbegin(); i != Matches_.rend(); i++) {
        std::cout << item << ") " << i->second << std::endl;
        item++;
    }
}

string Indexacao::normalizar(string palavra){

    map <char, char> acentos;
    acentos['Á'] = 'a'; acentos['À'] = 'a';
    acentos['Ã'] = 'a'; acentos['Â'] = 'a';
    acentos['Ä'] = 'a'; acentos['Å'] = 'a';
    acentos['Æ'] = 'e'; acentos['Ç'] = 'c';
    acentos['È'] = 'e'; acentos['É'] = 'e';
    acentos['Ê'] = 'e'; acentos['Ë'] = 'e';
    acentos['Í'] = 'i'; acentos['Ì'] = 'i';
    acentos['Î'] = 'i'; acentos['Ï'] = 'i';
    acentos['Ñ'] = 'n'; acentos['Ò'] = 'o';
    acentos['Ó'] = 'o'; acentos['Ô'] = 'o';
    acentos['Õ'] = 'o'; acentos['Ö'] = 'o';
    acentos['Ù'] = 'u'; acentos['Ú'] = 'u';
    acentos['Û'] = 'u'; acentos['Ü'] = 'u';
    acentos['Ý'] = 'y'; acentos['Þ'] = 'p';
    acentos['á'] = 'a'; acentos['à'] = 'a';
    acentos['â'] = 'a'; acentos['ã'] = 'a';
    acentos['ä'] = 'a'; acentos['å'] = 'a';
    acentos['æ'] = 'e'; acentos['ç'] = 'c';
    acentos['è'] = 'e'; acentos['é'] = 'e';
    acentos['ê'] = 'e'; acentos['ë'] = 'e';
    acentos['í'] = 'i'; acentos['ì'] = 'i';
    acentos['î'] = 'i'; acentos['ï'] = 'i';
    acentos['ð'] = 'O'; acentos['ñ'] = 'n';
    acentos['ó'] = 'o'; acentos['ò'] = 'o';
    acentos['ô'] = 'o'; acentos['õ'] = 'o';
    acentos['ö'] = 'o'; acentos['ú'] = 'u';
    acentos['ù'] = 'u'; acentos['û'] = 'u';
    acentos['ü'] = 'u'; acentos['ý'] = 'y';
    acentos['þ'] = 'p'; acentos['ÿ'] = 'y';
    
    string aux;

    for (auto &&i = palavra.begin(); i != palavra.end(); i++){
        if (acentos.count(*i)){
            *i = acentos[*i]; 
         }
        if (isalpha(*i)) aux += *i;
    }

    for ( int &&i = 0; i < aux.size(); i++){
        aux[i] = tolower(aux[i]);
    }

  return aux;
}

int Indexacao::tamanho(){
    return IndiceInvertido_.size();
}

set<string> Indexacao::busca_simples(string palavra){
    return IndiceInvertido_[palavra];
}

map<string,set<string>> Indexacao::IndiceInvertido(){
    return IndiceInvertido_;
}

Indexacao::~Indexacao(){}