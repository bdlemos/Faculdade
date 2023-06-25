#ifndef NODE_HPP
#define NODE_HPP

class Node {
    private:
        Node* left;
        Node* right;
        string Letter;
        int freq;
    public:
        Node(string Letter = "", int freq = 0, Node* left = nullptr, Node* right = nullptr){
            this->Letter = Letter;
            this->freq = freq;
            this->left = left;
            this->right = right;
        }
        Node* getLeft(){return left;}
        Node* getRight(){return right;}
        void setLeft(Node* left){this->left = left;}
        void setRight(Node* right){this->right = right;}
        string getLetter(){return Letter;}
        int getFreq(){return freq;}
        void setFreq(int freq){this->freq = freq;}
        bool operator>(Node& other){
            return freq > other.freq;
        }
        bool operator<(Node& other){
            return freq < other.freq;
        }
        bool operator==(Node& other){
            return freq == other.freq;
        }
        friend ostream& operator<<(ostream& os, Node& node){
            os << node.Letter << ": " << node.freq;
            return os;
        }
};

#endif