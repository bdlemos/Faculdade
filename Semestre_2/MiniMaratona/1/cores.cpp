#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main(){
    string s; cin >> s;
    if(s == "amarela" || s == "vermelha" || s == "azul") cout << "primaria";
    else if(s == "laranja" || s == "verde" || s == "roxa") cout << "secundario";
    else cout << "outra";
    cout << endl;
    return 0;
}
