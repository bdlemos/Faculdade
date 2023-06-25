#include <iostream>
#include <cmath>
#include <fstream>
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

void write_table(Node* ascii, ofstream& out){
    for(int i = 0; i < 256; i++){
        if(ascii[i].getFreq() != 0){
            out << i << ' ' << ascii[i].getFreq() << endl;
        }
    }
}

void read_table(Node* ascii, ifstream& in){
    int i, freq;
    while(in >> i >> freq){
        ascii[i].setFreq(freq);
    }
}

int main(int argc, char *argv[]){
    try{
        parse(argc, argv);
        if (opt == 'c'){
            
            //Create frequency table
            Node ascii[256];
            for(int i = 0; i < 256; i++) ascii[i] = Node(string(1,i), 0);
            
            //Read file
            ifstream in(Fin);
            if (!in.is_open()) throw "File not found";
            char c;
            string text = "";
            while(in.get(c)){
                ascii[int(c)].setFreq(ascii[int(c)].getFreq()+1);
                text += c;
            }
            in.close();

            //Create heap and Huffman tree
            MinHeap<Node> heap(ascii,256);
            Huffman Encode(heap);
            string Code = Encode.code(text);
            //write the code in a binary file
            int extra_bits = 8 - Code.size() % 8;
            ofstream out(Fout, ios::out | ios::binary);
            out << extra_bits;
            Encode.write_bits(Code, out);
            out.close();

            //Write table in a file
            ofstream table("table.txt", ios::out);
            write_table(ascii, table);

            cout << "Sucessfully compressed file\n";
        }else if (opt == 'd'){
            
            //Read table of frequencies
            Node ascii[256];
            for(int i = 0; i < 256; i++) ascii[i] = Node(string(1,i), 0);
            ifstream table("table.txt", ios::in);
            read_table(ascii, table);
            table.close();

            //Create heap and Huffman tree
            MinHeap<Node> heap(ascii,256);
            Huffman key(heap);

            //Read compressed file
            ifstream in(Fin, ios::in | ios::binary);
            if (!in.is_open()) throw "File not found";
            char extra_bits;
            in.get(extra_bits);
            string code = key.read_bits(in, extra_bits - '0');
            in.close();

            string original = key.decode(code);

            //Write descompressed in a file
            ofstream decode(Fout, ios::out);
            decode << original;
            decode.close();

            cout << "Sucessfully descompressed file\n";
        }
    }catch(const char* e){
        cout << e << endl;
    }
    return 0;
}