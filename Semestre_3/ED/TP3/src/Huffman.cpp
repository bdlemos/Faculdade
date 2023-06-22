#include "Huffman.hpp"

using namespace std;

Huffman::Huffman(MinHeap<Node>& heap){
    while(heap.getSize() > 1){
        Node aux = heap.ExtractMin();
        Node* left =  new Node(aux.getLetra(), aux.getFreq(), aux.getLeft(), aux.getRight());
        
        aux = heap.ExtractMin();
        Node* right = new Node(aux.getLetra(), aux.getFreq(), aux.getLeft(), aux.getRight());

        Node node = Node("#", left->getFreq() + right->getFreq());
        node.setLeft(left);
        node.setRight(right);
        heap.Insert(node);
    }
    Node aux = heap.ExtractMin();
    root = new Node(aux.getLetra(), aux.getFreq(), aux.getLeft(), aux.getRight());
}

Huffman::~Huffman(){
    delete_tree(root);
}

void Huffman::delete_tree(Node* node){
    if(node != nullptr){
        delete_tree(node->getLeft());
        delete_tree(node->getRight());
        delete node;
    }
}

void Huffman::print_codes(Node* node, string code){
    if(node != nullptr){
        if(node->getLetra() != "#"){
            cout << node->getLetra() << " " << code << endl;
        }
        print_codes(node->getLeft(), code+"0");
        print_codes(node->getRight(), code+"1");
    }
}

string Huffman::code(string letra){
    string code = "";
    for(auto i : letra){
        code += get_code(root, string(1,i), "");
    }
    return code;
}

string Huffman::decode(string code){
    string word = "";
    Node* aux = root;
    for(auto i : code){
        if(i == '0'){
            aux = aux->getLeft();
        }else{
            aux = aux->getRight();
        }
        if(aux->getLetra() != "#"){
            word += aux->getLetra();
            aux = root;
        }
    }
    return word;
}

string Huffman::get_code(Node* node, string letra, string code){
    if(node != nullptr){
        if(node->getLetra() == letra){
            return code;
        }
        string aux = get_code(node->getLeft(), letra, code+"0");
        if(aux != ""){
            return aux;
        }
        aux = get_code(node->getRight(), letra, code+"1");
        if(aux != ""){
            return aux;
        }
    }
    return "";
}