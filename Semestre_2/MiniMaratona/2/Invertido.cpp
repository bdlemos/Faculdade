#include <bits/stdc++.h>
 
using namespace std;
 
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define f first
#define s second
 
typedef long long ll;
 
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

bool primo (ll n){
    for(ll i = 2 ; i*i < n; i++){
        if(!(n%i)) return false;
    }
    return true;
} 

int main() { _
    ll x;
    vector<bool> primos(pow(2,31),false);
    vector<bool> p(pow(2,31),false);
    while (cin >> x){
        string s = to_string(x);
        string inverse;
        for (int i = s.length() - 1; i >= 0; i--) inverse += s[i];
        ll inv = stoll(inverse);
        if(!p[inv] and primo(inv))
            primos[inv] = p[inv] = true;
        if(!p[x] and primo(x))
            primos[x] = p[x] = true;
        if(primos[x] and primos[inv] and x!=inv)
            cout << x << " omirp" << endl;
        else if(primos[x])
            cout << x << " primo"<< endl;
        else
            cout << x << " nao primo" << endl;
    }

    return 0;
}