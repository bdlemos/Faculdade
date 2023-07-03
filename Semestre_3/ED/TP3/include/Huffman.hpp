#ifndef HUFFMAN
#define HUFFMAN

#include <iostream>
#include <fstream>
#include <MinHeap.hpp>
#include <Node.hpp>

class Huffman {
    private:
        Node* root;
        std::string AsciiCodes[256];
        
        //Fill the table of codes of chars
        void Fullfill_table();
        //Delete tree
        void Delete_tree(Node* node);
        //Receive a char and return the code
        std::string Get_code(Node* node, char character, std::string code);
        //Receive a text and return the code
        std::string Code(std::string& character);
        //Receive a code and return the string
        std::string DecodedString(std::string& code);
        //Receive a strinf of bits and write bits in file
        void Write_bits(std::string& bits, std::ofstream& out);
        //Receive a file and return a string of bits
        std::string Read_bits(std::ifstream& in, int extra_bits);
        //Build the tree of ocorrrences of chars
        void Build_tree(MinHeap<Node>& heap);
        //Write the table of ocorrrences in file
        void Write_table(Node* ascii, std::ofstream& out);
        //Read the table of ocorrrences in file
        void Read_table(Node* ascii, std::ifstream& in);
    public:
        //Has 2 modes: compress and decompress, the default is compress
        //Compress: Receive a file to compress and a file to write the compressed file
        //Decompress:  Receive a compressed file, a file to write the decompressed file, a table of ocorrrences and the option 'd'
        Huffman(std::string Fin, std::string Fout, char opt = 'c');
        ~Huffman();
        //Compress a file
        //Receive a file to compress and a file to write the compressed file
        void Encode(std::string Fin, std::string Fout);
        //Decompress a file
        //Receive a compressed file, a file to write the decompressed file and a table of ocorrrences
        void Decode(std::string Fin, std::string Fout ,std::string Table);
};
#endif