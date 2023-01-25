#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main(){
    string s;
    int cont = 0;
    while(cin >> s) cont+=s.size() + 1;
    cout << --cont;
}
