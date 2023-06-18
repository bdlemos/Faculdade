#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);

typedef unsigned long long int ll;

const int INF = 0x3f3f3f3f;
const ll LINF= 0x3f3f3f3f3f3fll;

int main() { _
        ll n;
        int cont=1;
        while(cin >> n){
            ll ans=1;
            for (int i = 1; i <= n; i++) ans *= i;
            
            string s = to_string(ans);
            for (int i = s.length() - 1; i >= 0; i--){
                if(s[i] != '0'){
                    cout << "Instancia " << cont << endl;
                    cout << s[i]<< endl;
                    break;
                }
            }
            cont++;
        }
        
    return 0;
}