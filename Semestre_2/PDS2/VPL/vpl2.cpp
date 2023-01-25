#include <iostream>

using namespace std;

void vow_num(string s);

int main() {
    string word;
    cin >> word;
    vow_num(word);
    return 0;
}

void vow_num(string s){
    int a, e, i, o, u;
    a = e = i = o = u = 0;
    for (int j = 0; j < s.length(); j++){
        if (s[j] == 'a')
            a++;
        else if (s[j] == 'e')
            e++;
        else if (s[j] == 'i')
            i++;
        else if (s[j] == 'o')
            o++;
        else if (s[j] == 'u')
            u++;
        else
            continue;
    }
    if (a != 0)
        cout << "a " << a << endl;
    if (e != 0)
        cout << "e " << e << endl;
    if (i != 0)
        cout << "i " << i << endl;
    if (o != 0)
        cout << "o " << o << endl;
    if (u != 0)
        cout << "u " << u << endl;
    
}