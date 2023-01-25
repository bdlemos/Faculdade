#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main(){
    int t; cin >> t;
    while (t--){
        ll ans = 0, menor = 0, cont = 0, aux;
        int n; cin >> n;
        vector<int> price;
        for (int i = 0; i < n; i++){
            cin >> aux;
            price.push_back(aux);
        }
        menor = *price.rbegin();
        for (auto it = price.rbegin(); it != price.rend(); it++){
            if (*it > menor)cont++;
            else if(*it < menor){menor = *it; ans += cont; cont = 0;}
        }
        ans += cont;
        
        cout << ans << endl;
    }
    return 0;
}