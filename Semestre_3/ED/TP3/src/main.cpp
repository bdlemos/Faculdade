#include <iostream>
#include <MinHeap.hpp>
#include <Huffman.hpp>
#include <Node.hpp>

using namespace std;

char opt;
string Fin;
string Fout;
string coded;

void parse(int argc, char *argv[]){
    for(int i = 0; i < argc; i++){
        if(string(argv[i]) == "-c") {
            if(i + 2 >= argc) throw "Invalid arguments";
            opt = 'c';
            Fin = argv[i+1];
            Fout = argv[i+2];
            return;
        }
        else if(string(argv[i]) == "-d") {
            if(i + 3 >= argc) throw "Invalid arguments";
            opt = 'd';
            Fin = argv[i+1];
            Fout = argv[i+2];
            coded = argv[i+3];
            return;
        }
    }
    throw "Invalid arguments";
}

int main(int argc, char *argv[]){
    try{
        parse(argc, argv);
        if (opt == 'c'){
            Huffman huffman(Fin, Fout);
        }else if (opt == 'd'){
            Huffman huffman(Fin, Fout, coded, opt);
        }
    }catch(const char* e){
        cout << e << endl;
    }
    return 0;
}