#include <bits/stdc++.h>
#include <cmath>

using namespace std;
using std::string;

// Tranform a binary string to a hex string
string BinToHex(string bin_string){
    bitset<32> bin_value(bin_string);
    unsigned int decimal_value = bin_value.to_ulong();

    stringstream ss;
    ss << hex << decimal_value;
    string hex_string = ss.str();
    for (char &c : hex_string) {
        c = std::toupper(c);
    }

    return hex_string;
}

// Tranform a hex string to a binary string
string HexToBin(string hex_string){
    stringstream ss;
    ss << hex << hex_string;
    unsigned int decimal_value;
    ss >> decimal_value;

    bitset<32> binary_value(decimal_value);

    return binary_value.to_string();
}


// Auxiliary function to remove n bits related to a block size offset
string BinaryTreatment(string bin_string, int offset){
    for (int i = bin_string.length() - offset; i < bin_string.length(); i++){
        bin_string[i] = '0';
    }
    bitset<32> bin_value(bin_string);
    bin_string = bin_value.to_string();

    return bin_string;
}

//Auxiliary function to verify if a adress is in a set
bool find(list<string> bloco, string value){
    for (auto it = bloco.begin(); it != bloco.end(); it++){
        if (*it == value) return true;
    }
    return false;
}


// Print matrix when is totally associative
void PrintMat(vector<string> mat, int size_x, ofstream &output_file){
    cout << "================\n" << "IDX V ** ADDR **" << endl;
    output_file << "================\n" << "IDX V ** ADDR **" << endl;
    for (int i = 0; i < size_x; i++){
        string hex_addr = BinToHex(mat[i]), idx = to_string(i);

        int idx_size = idx.length();
        for (int j = 3 - idx_size; j > 0; j--) idx = '0' + idx;

        int hex_addr_size = hex_addr.length();
        for (int j = 8 - hex_addr_size; j > 0; j--) hex_addr = '0' + hex_addr;

        int valid_bit = (mat[i] == "") ? 0 : 1;
        cout << idx << " " << valid_bit;
        output_file << idx << " " << valid_bit;
        if (valid_bit) {cout << " 0x" << hex_addr << endl; output_file << " 0x" << hex_addr << endl;}
        else {cout << "" << endl; output_file << "" << endl;}
    }
}


// Print matrix when is N-way associative
void Print(vector<list<string>> mat, int associativity, ofstream &output_file){
    cout << "================\n" << "IDX V ** ADDR **" << endl;
    output_file << "================\n" << "IDX V ** ADDR **" << endl;
    int count = 0;
    for(auto i : mat){
        for (auto j : i){
            string hex_addr = BinToHex(j), idx = to_string(count++);

            int idx_size = idx.length();
            for (int j = 3 - idx_size; j > 0; j--) idx = '0' + idx;

            int hex_addr_size = hex_addr.length();
            for (int j = 8 - hex_addr_size; j > 0; j--) hex_addr = '0' + hex_addr;

            int valid_bit = (j.empty()) ? 0 : 1;
            
            cout << idx << " " << valid_bit;
            output_file << idx << " " << valid_bit;

            if (valid_bit) {cout << " 0x" << hex_addr << endl; output_file << " 0x" << hex_addr << endl;}
            else {cout << "" << endl; output_file << "" << endl;}
        }
        for(int j = i.size(); j < associativity; j++){
            string idx = to_string(count++);

            int idx_size = idx.length();
            for (int j = 3 - idx_size; j > 0; j--) idx = '0' + idx;

            cout << idx << " 0" << endl;
            output_file << idx << " 0" << endl;
        
        }
    }
}

int main(int argc, char const *argv[]) {
    // Reading arguments
    int cache_size = atoi(argv[1]), line_size = atoi(argv[2]), group_size = atoi(argv[3]);
    string file_name = argv[4];
    
    // Reading input file
    ifstream file(file_name);
    vector<string> addresses;
    string line;
    while (getline(file, line)) addresses.push_back(line);
    

    // Making cache
    int cache_lines = cache_size / line_size;
    int numbers_sets = cache_lines / group_size;
    int hit = 0, miss = 0;


    // Making convertions
    vector<string> binary_addresses;
    for (auto hex_string : addresses) {
        string binary_value = HexToBin(hex_string);
        string treated_binary_value = BinaryTreatment(binary_value, log2(line_size)); // block size offset
        binary_addresses.push_back(binary_value);
    }

    ofstream output_file;
    output_file.open("output.txt");


    if (numbers_sets == 1){  // Totally associated
        vector<string> cache(cache_lines);
        int fifo = 0; // FIFO pointer
        for (int i = 0; i < cache_lines; i++) cache[i] = "";
        
        for (auto binary_addr : binary_addresses){

            bitset<32> binary_addr_value(binary_addr);
            binary_addr_value = binary_addr_value >> log2(line_size);
            binary_addr = binary_addr_value.to_string();
            for (int i = 0; i < cache_lines; i++){
                if (cache[i] == ""){ 
                    cache[i] = binary_addr;
                    miss++;
                    break;
                }
                if (cache[i] == binary_addr){
                    hit++;
                    break;
                }
                if (i == (cache_lines-1)){
                    cache[fifo] = binary_addr;
                    fifo = (fifo + 1) % cache_lines;
                    miss++;
                }
            }
            PrintMat(cache, cache_lines, output_file);
        }
    }else if (numbers_sets == cache_lines){ // Direct mapped
        vector<string> cache(cache_lines);
        for (int i = 0; i < cache_lines; i++) cache[i] = "";

        int index_size = log2(cache_lines);
        int tag_size = 32 - log2(line_size) - index_size;

        for (auto binary_addr : binary_addresses) {
            
            // index: position where the address should be placed in the cache
            string index_str = binary_addr.substr(tag_size, index_size);
            bitset<32> index_value(index_str);
            ulong index = index_value.to_ulong();
            //int index = stoi(binary_addr.substr(tag_size+1, index_size), 0, 2);
            
            bitset<32> binary_addr_value(binary_addr);
            binary_addr_value = binary_addr_value >> log2(line_size);
            binary_addr = binary_addr_value.to_string();

            // if the position is empty -> put (miss)
            if (cache[index] == "") {
                cache[index] = binary_addr;
                miss++;

            // if the data is already in the position -> keep (hit)
            } else if (cache[index] == binary_addr) {
                hit++;
            
            // if the position is occupied -> change (miss)
            } else {
                cache[index] = binary_addr;
                miss++;
            }

            PrintMat(cache, cache_lines, output_file);
        }
    }else{
        vector<list<string>> cache(numbers_sets);
        vector<int> fifo(numbers_sets,0);

        // Calculating sizes of tag and index
        int index_size = log2(numbers_sets);
        int tag_size = 32 - log2(line_size) - index_size;


        for (auto binary_addr : binary_addresses){
            // Getting tag and index from address
            string tag = binary_addr.substr(0, tag_size);
            string index = binary_addr.substr(tag_size, index_size);

            // Removing the block identifier from the address to put on cache
            bitset<32> binary_addr_value(binary_addr);
            binary_addr_value = binary_addr_value >> log2(line_size);
            binary_addr = binary_addr_value.to_string();

            // Converting index to int
            bitset<32> index_value(index);
            ulong index_int = index_value.to_ulong();
            index_int = index_int % numbers_sets;

            // Checking if the address is already in the cache
            if(find(cache[index_int], binary_addr)){
                hit++;
            }
            // Else the address is not in the cache
            else{
                // If the set is not full
                if (cache[index_int].size() < group_size){
                    cache[index_int].push_back(binary_addr);
                }
                // If the set is full, remove the first element and put the new one (FIFO)
                else{
                    auto it = cache[index_int].begin();
                    advance(it, fifo[index_int]);
                    *it = binary_addr;
                    fifo[index_int] = (fifo[index_int] + 1) % group_size;
                }
                miss++;
            }
            Print(cache, group_size, output_file);
        }
    }

    cout << endl << "#hits: " << hit << endl << "#miss: " << miss << endl;
    //write output file
    output_file<< endl << "#hits: " << hit << endl << "#miss: " << miss << endl;
    return 0;
}