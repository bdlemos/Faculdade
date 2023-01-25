#include <iostream>
#include <map>  // Isto é uma dica. 

using namespace std;

int main() {
    string s;
    map<string,int> words;

    while (cin >> s){
        try{
            words.at(s);
            words[s]++;
        }
        catch(exception& e){
            words.insert({s, 1});
        }
    }
    
    string max;
    int maxnum = 0;
    for (auto i : words){
        if (i.second > maxnum){
            maxnum = i.second;
            max = i.first;
        }
    }
    
    cout << max << endl;
    return 0;
}