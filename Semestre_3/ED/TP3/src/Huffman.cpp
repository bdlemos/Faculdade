#include "Huffman.hpp"

using namespace std;

Huffman::Huffman(string Fin, string Fout, string Table , char opt){
    if(opt == 'c'){
        Encode(Fin, Fout);
    }else if(opt == 'd'){
        Decode(Fin, Fout, Table);
    }else{
        throw "Invalid option";
    }
}

void Huffman::Build_tree(MinHeap<Node>& heap){
    while(heap.getSize() > 1){
        Node aux = heap.ExtractMin();
        Node* left =  new Node(aux.getLetter(), aux.getFreq(), aux.getLeft(), aux.getRight());
        
        aux = heap.ExtractMin();
        Node* right = new Node(aux.getLetter(), aux.getFreq(), aux.getLeft(), aux.getRight());

        Node node = Node(0, left->getFreq() + right->getFreq());
        node.setLeft(left);
        node.setRight(right);
        heap.Insert(node);
    }
    Node aux = heap.ExtractMin();
    root = new Node(aux.getLetter(), aux.getFreq(), aux.getLeft(), aux.getRight());
}

Huffman::~Huffman(){
    Delete_tree(root);
}

void Huffman::Delete_tree(Node* node){
    if(node != nullptr){
        Delete_tree(node->getLeft());
        Delete_tree(node->getRight());
        delete node;
    }
}

string Huffman::Code(string Letter){
    string code = "";
    for(auto i : Letter){
        code += Get_code(root, i, "");
    }
    return code;
}

string Huffman::DecodedString(string code){
    string word = "";
    Node* aux = root;
    for(auto i : code){
        if(i == '0'){
            aux = aux->getLeft();
        }else{
            aux = aux->getRight();
        }
        if(aux->getLetter() != 0){
            word += aux->getLetter();
            aux = root;
        }
    }
    return word;
}

string Huffman::Get_code(Node* node, char Letter, string code){
    if(node != nullptr){
        if(node->getLetter() == Letter){
            return code;
        }
        string aux = Get_code(node->getLeft(), Letter, code+"0");
        if(aux != ""){
            return aux;
        }
        aux = Get_code(node->getRight(), Letter, code+"1");
        if(aux != ""){
            return aux;
        }
    }
    return "";
}

void Huffman::Write_bits(string bits, ofstream& out){
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

string Huffman::Read_bits(ifstream& in, int extra_bits){
    if (extra_bits == 8) extra_bits = 0;

    string bits = "";
    char c;
    int i;
    
    while(in.get(c)){
        for(i = 7; i >= 0; i--){
            char bit = ((c >> i) & 1) ? '1' : '0';
            bits += bit;
        }
    }
    
    //Remove extra bits
    int size = bits.size();
    if (extra_bits != 0)
        bits.erase(size - 8, extra_bits);
    return bits;
}

void Huffman::Encode(string Fin, string Fout){
           
            //Create frequency table
            Node ascii[256];
            for(int i = 0; i < 256; i++) ascii[i] = Node(i, 0);
            
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
            Build_tree(heap);
            string StringCode = Code(text);

            //write the code in a binary file
            int extra_bits = 8 - StringCode.size() % 8;
            ofstream out(Fout, ios::out | ios::binary);
            out << extra_bits;
            Write_bits(StringCode, out);
            out.close();

            //Write table in a file
            ofstream table("table.txt", ios::out);
            Write_table(ascii, table);
            table.close();

            cout << "Sucessfully compressed file\n";
}

void Huffman::Decode(string Fin, string Fout ,string Table){

            //Read table of frequencies
            Node ascii[256];
            for(int i = 0; i < 256; i++) ascii[i] = Node(i, 0);
            std::ifstream table(Table, ios::in);
            Read_table(ascii, table);
            table.close();

            //Create heap and Huffman tree
            MinHeap<Node> heap(ascii,256);
            Build_tree(heap);

            //Read compressed file
            ifstream in(Fin, ios::in | ios::binary);
            if (!in.is_open()) throw "File not found";
            char extra_bits;
            in.get(extra_bits);
            string code = Read_bits(in, extra_bits - '0');
            in.close();

            string original = DecodedString(code);

            //Write descompressed in a file
            ofstream decoded(Fout, ios::out);
            decoded << original;
            decoded.close();

            cout << "Sucessfully descompressed file\n";
}

void Huffman::Write_table(Node* ascii, ofstream& out){
    for(int i = 0; i < 256; i++){
        if(ascii[i].getFreq() != 0){
            out << i << ' ' << ascii[i].getFreq() << std::endl;
        }
    }
}

void Huffman::Read_table(Node* ascii, ifstream& in){
    int i, freq;
    while(in >> i >> freq){
        ascii[i].setFreq(freq);
    }
}