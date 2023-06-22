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
int current_bit = 0;
unsigned char bit_buffer;

void parse(int argc, char *argv[]){
    for(int i = 0; i < argc; i++){
        if(string(argv[i]) == "-c") {
            opt = 'c';
            Fin = string(argv[i+1]);
            Fout = string(argv[i+2]);
            return;
        }
        else if(string(argv[i]) == "-d") {
            opt = 'd';
            Fin = string(argv[i+1]);
            Fout = string(argv[i+2]);
            return;
        }
    }
    throw "Invalid arguments";
}

void write_bits(string bits, ofstream& out){
    int i = 0;
    int size = bits.size();
    while(i < size){
        char c = 0;
        for(int j = 0; j < 8; j++){
            if(i+j < size){
                c = c << 1;
                if(bits[i+j] == '1') c = c | 1;
            }else break;
        }
        out << c;
        i += 8;
    }
}

string read_bits(ifstream& in, int size){
    int extra_bits = 8 - size % 8;
    if (extra_bits == 8) extra_bits = 0;

    string bits = "";
    int count = 0;
    char c;
    int i;
    
    while(in.get(c)){
        count++;
        if (count != ceil(float(size)/8)){
            for(i = 7; i >= 0; i--){
                char bit = ((c >> i) & 1) ? '1' : '0';
                bits += bit;
            }
        }else{
            for(i =  7 - extra_bits; i >= 0; i--){
                char bit = ((c >> i) & 1) ? '1' : '0';
                bits += bit;
            }
            break;
        }
    }
    return bits;
}


int main(int argc, char *argv[]){
    try{
        //Node v[6] = {Node("a", 45), Node("b", 13), Node("c", 12), Node("d", 16), Node("e", 9), Node("f", 5)};
        parse(argc, argv);
        Node ascii[256];
        for(int i = 0; i < 256; i++) ascii[i] = Node(string(1,i), 0);
        
        ifstream in(Fin);
        if (!in.is_open()) throw "File not found";
        
        char c;
        string text = "";
        while(in.get(c)){
            ascii[int(c)].setFreq(ascii[int(c)].getFreq()+1);
            text += c;
        }
        in.close();
        
        MinHeap<Node> heap(ascii,256);
        Huffman code(heap);
        string Code = code.code(text);
        
        //write the code in a binary file
        ofstream out(Fout, ios::out | ios::binary);
        write_bits(Code, out);
        out.close();
        
        //Descompress test
        ifstream in2(Fout, ios::in | ios::binary);
        string s = read_bits(in2, Code.size());
        in2.close();
        string decoded = code.decode(s);

        //Write descompressed in a file
        ofstream decode("decoded.txt", ios::out);
        decode << decoded;
        decode.close();
        cout << "Sucessfully compressed file\n";
    }catch(const char* e){
        cout << e << endl;
    }
    return 0;
}