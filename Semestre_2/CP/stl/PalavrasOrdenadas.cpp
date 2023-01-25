#include<bits/stdc++.h>

using namespace std;

int main(){
    int n; cin >> n;
    string k;
    while (n--){
        cin >> k;
        bool c = true;
        for (int i = 0; i < k.length() - 1; i++){
            char K = tolower(k[i]);
            char K1 = tolower(k[i+1]);
            if(K >= K1) {c = false;break;};
        }
        if(c) cout << k << ": " << "O" << endl;
        else cout << k << ": " << "N" << endl;
    }
    
    return 0;
}