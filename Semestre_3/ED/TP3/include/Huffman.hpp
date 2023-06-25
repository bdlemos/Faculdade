#ifndef HUFFMAN
#define HUFFMAN

#include <iostream>
#include <fstream>
#include <MinHeap.hpp>
#include <Node.hpp>

class Huffman {
    private:
        Node* root;
        void delete_tree(Node* node);
        std::string get_code(Node* node, std::string letra, std::string code);
    public:
        Huffman(MinHeap<Node>& heap);
        ~Huffman();
        void print_codes(Node* node, string code);
        std::string code(std::string letra);
        std::string decode(std::string code);
        void write_bits(std::string bits, std::ofstream& out);
        std::string read_bits(std::ifstream& in, int extra_bits);
};
#endif