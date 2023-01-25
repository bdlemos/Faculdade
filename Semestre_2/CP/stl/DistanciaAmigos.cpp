#include <bits/stdc++.h>
typedef long long ll;
 
using namespace std;
 
int main(){
    ll n; cin >> n;
    ll start, ans = 0;
    ll aux = -9999999999;
    vector<ll> p;
    
    for (ll i = 0; i < n; i++){
        ll x; cin >> x;
        p.push_back(x);
        if(p[i] - i > aux) {aux = p[i] - i;start = i;};
    }
    for (int i = start + 1; i < p.size(); i++){
        ans = max(ans, aux + p[i] + i);
    }

    
    cout << ans;
}