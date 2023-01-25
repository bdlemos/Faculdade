#include <bits/stdc++.h>
 
using namespace std;
 
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define f first
#define s second
 
typedef long long ll;
 
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;
const ll LMIN = -0x3f3f3f3f3f3f3f3fll;
 
int main() { _
    int t; cin >> t;
    while (t--){
        vector<ll> v;
        int n; cin >> n;
        for (int i = 0; i < n; i++) {int x;cin >> x; v.push_back(x);}
        ll ans = 0;
        bool positivo = v[0] > 0 ? true : false; // true =  positivo false = negativo
        ll maior = v[0];
        for (int i = 1; i < v.size();i++){
            if((positivo and v[i] > 0) or (!positivo and v[i] < 0))
                maior = (v[i] > maior) ? v[i] : maior;
            else if(positivo and v[i] < 0) {positivo = false; ans += maior; maior = v[i];}
            else if(!positivo and v[i] > 0) {positivo = true; ans += maior; maior = v[i];}
        }
        if(!positivo and maior < 0) ans += maior;
        else if(positivo and maior > 0) ans += maior;
        cout << ans << endl;
    }
    
    return 0;
}