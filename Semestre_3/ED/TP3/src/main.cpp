#include <iostream>
#include <MinHeap.hpp>
#include <Huffman.hpp>
#include <Node.hpp>
#include <chrono>

using namespace std;

char opt;
string Fin;
string Fout;

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
            if(i + 2 >= argc) throw "Invalid arguments";
            opt = 'd';
            Fin = argv[i+1];
            Fout = argv[i+2];
            return;
        }
    }
    throw "Invalid arguments";
}

int main(int argc, char *argv[]){
    try{
        parse(argc, argv);
        if (opt == 'c'){
            auto start = chrono::high_resolution_clock::now();
            Huffman huffman(Fin, Fout);
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
            cout << "Time: " << duration.count() << "ms" << endl;
        }else if (opt == 'd'){
            auto start = chrono::high_resolution_clock::now();
            Huffman huffman(Fin, Fout, opt);
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
            cout << "Time: " << duration.count() << "ms" << endl;
        }
    }catch(const char* e){
        cout << e << endl;
    }
    return 0;
}