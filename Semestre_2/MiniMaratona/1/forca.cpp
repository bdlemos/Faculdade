#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main(){
    int n = 0;
    cin >> n;
    while(n != -1){
        vector<int> w(26,0);
        int e = 0;
        bool c = true;
        string s; cin >> s;
        for (auto &&i : s){
            i -= 'a';
            w[i] = 1;
        }
        string ans; cin >> ans;
        for (auto &&i : w){
            if(w[i] == 1)w[i]++;
            else e++;
        }
        for (auto &&i : w) if(i == 1) c = false;
        
        cout << "Jogo " << n << endl;
        if(e < 7 and c) cout << "ganhou." << endl;
        else if( e >= 7) cout << "perdeu." << endl;
        else cout << "desistiu." << endl;
        cin >> n;
    }
    return 0;
}