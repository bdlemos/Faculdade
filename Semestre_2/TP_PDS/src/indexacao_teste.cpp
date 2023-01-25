#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "indexacao.h"

TEST_CASE("Testa Indexacao::normalizar(palavra)"){
    Indexacao i;
    CHECK(i.normalizar("guárdâ-chüvà") == "guardachuva");
    CHECK(i.normalizar("ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÑÒÓÔÕÖÙÚÛÜ") == "aaaaaaeceeeeiiiinooooouuuu");
    CHECK(i.normalizar("ÝÞàáâãäåæçèéêëìíîïðñòóôõöùúûüýþÿ") == "ypaaaaaaeceeeeiiiionooooouuuuypy");
    CHECK(i.normalizar("-Programação e Desenvolvimento De Software.") == "programacaoedesenvolvimentodesoftware");
}

TEST_CASE("Testa Indexacao::tamanho()"){
    Indexacao i;
    i.adicionar("./documentos_teste/");
    CHECK(i.tamanho() == 8);
}

TEST_CASE("Testa Indexacao::buscar(palavras_buscadas)"){
    Indexacao i;
    
    i.adicionar("./documentos_teste/");

    multimap<int,string> Mapa;
    Mapa.insert({1,"d1.txt"});
    vector <string> Teste = {"trabalho"};

    CHECK(i.buscar(Teste) == Mapa);

    Mapa.insert({2, "hello"});
    CHECK_FALSE(i.buscar(Teste) == Mapa);

    Mapa.clear();
    Teste.clear();

    Mapa.insert({5,"d5.txt"});
    Mapa.insert({5,"d4.txt"});
    Teste = {"Programação", "e", "Desenvolvimento", "de", "Software"};
    CHECK(i.buscar(Teste) == Mapa);
}

TEST_CASE("Testa Indexacao::busca_simples()"){
    Indexacao i;
    
    i.adicionar("./documentos_teste/");
    set<string> t;
    
    t.insert("d2.txt");
    CHECK(i.busca_simples("pratico") == t);
    
    t.erase("d2.txt"); t.insert("d1.txt");
    CHECK(i.busca_simples("trabalho") == t);
    
    t.erase("d1.txt"); t.insert("d3.txt");
    CHECK(i.busca_simples("pds") == t);
}

TEST_CASE("Testa Indexacao::adicionar(diretorio)"){
    Indexacao i;
    
    i.adicionar("./documentos_teste/");
    map<string,set<string>> Indice;
    set<string> aux; 
    
    aux.insert("d1.txt");
    Indice.insert({"trabalho", aux});

    aux.clear(); aux.insert("d2.txt");
    Indice.insert({"pratico", aux});    

    aux.clear(); aux.insert("d3.txt");
    Indice.insert({"pds", aux}); 

    aux.clear(); aux.insert("d4.txt"); aux.insert("d5.txt");
    Indice.insert({"programacao", aux});
    Indice.insert({"e", aux});
    Indice.insert({"desenvolvimento", aux});
    Indice.insert({"de", aux});
    Indice.insert({"software", aux});

    CHECK(i.IndiceInvertido() == Indice);
}