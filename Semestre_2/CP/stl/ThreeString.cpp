#include <bits/stdc++.h>

using namespace std;

int main(){
    int n; cin >> n;
    string a, b, c;
    while (cin >> a >>b >> c){
        bool  condition = true;
        for (int i = 0; i < c.length(); i++){
            if (c[i] != a[i] && c[i] != b[i]) condition = false;
        }
        if(condition) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}