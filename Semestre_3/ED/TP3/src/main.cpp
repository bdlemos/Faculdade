#include <iostream>
#include <MinHeap.hpp>
#include <Node.hpp>

using namespace std;

void delete_tree(Node* node){
    if(node != nullptr){
        delete_tree(node->getLeft());
        delete_tree(node->getRight());
        delete node;
    }
}

void print_codes(Node* node, string code){
    if(node != nullptr){
        if(node->getLetra() != "#"){
            cout << node->getLetra() << " " << code << endl;
        }
        print_codes(node->getLeft(), code+"0");
        print_codes(node->getRight(), code+"1");
    }
}

string get_code(Node* node, string letra, string code){
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

string code(Node* node, string letra){
    string code = "";
    for(auto i : letra){
        code += get_code(node, string(1,i), "");
    }
    return code;
}

string decode(Node* node, string code){
    string word = "";
    Node* aux = node;
    for(auto i : code){
        if(i == '0'){
            aux = aux->getLeft();
        }else{
            aux = aux->getRight();
        }
        if(aux->getLetra() != "#"){
            word += aux->getLetra();
            aux = node;
        }
    }
    return word;
}

Node* Huffman(MinHeap<Node>& heap){
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
    return new Node(aux.getLetra(), aux.getFreq(), aux.getLeft(), aux.getRight());
}

int main(){
    try{
        Node v[6] = {Node("a", 45), Node("b", 13), Node("c", 12), Node("d", 16), Node("e", 9), Node("f", 5)};
        MinHeap<Node> heap(v,6);
        Node* root = Huffman(heap);
        //print_codes(root, "");
        string word = "bad";
        
        string Code = code(root, word);
        cout << Code << endl;
        
        cout << decode(root, Code);

        cout << endl;
        delete_tree(root);
    }catch(const char* e){
        cout << e << endl;
    }
    return 0;
}