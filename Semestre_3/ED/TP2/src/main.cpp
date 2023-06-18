#include<bits/stdc++.h>
#include "Graham.hpp"
#include "Jarvis.hpp"

using namespace std;

void automatizar(string algoritmo,string metodo, string arquivo);

int main(int argc, char *argv[]){
    if (argc < 2){
        cout << "Nenhum arquivo passado para leitura" << endl << "Uso: ./TP2 <nome do arquivo>" << endl;
        return 0;
    }
    try {
        
        Graham* Fecho0 = new Graham(argv[1]);
        Fecho0->Resolve("Insertion");
        cout << "FECHO CONVEXO: " << endl;
        Fecho0->ImprimePontos();
        cout << endl;
        if(argc > 2 and string(argv[2]) == "-r"){
            cout << "FECHO CONVEXO COM RETAS: " << endl;
            Fecho0->ImprimeRetas();
            cout << endl;
        }
        delete Fecho0;
        
        cout << fixed << setprecision(3);
        
        cout << "GRAHAM+MERGESORT: ";
        automatizar("Graham","Merge", argv[1]);
        
        cout << "GRAHAM+INSERTIONSORT: ";
        automatizar("Graham","Insertion", argv[1]);

        cout << "GRAHAM+LINEARSORT: ";
        automatizar("Graham","Linear", argv[1]);

        cout << "JARVIS: ";
        automatizar("Jarvis","", argv[1]);

        //arquivo.open("Jarvis.csv", ios::out | ios::app);
        // arquivo << s << ',' << time << endl;
        //arquivo.close();
    }
    catch (string erro){
        cout << erro << endl;
    }
    return 0;
}

void automatizar(string algoritmo, string metodo, string arquivo){
    if(algoritmo == "Graham"){
        Graham* Fecho = new Graham(arquivo);
        float time = Fecho->Tempo(metodo);
        cout << time << 's' << endl;
        delete Fecho;
    }else if(algoritmo == "Jarvis"){
        Jarvis* Fecho = new Jarvis(arquivo);
        float time = Fecho->Tempo(metodo);
        cout << time << 's' << endl;
        delete Fecho;
    }
}