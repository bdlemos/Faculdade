#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define f first
#define s second


typedef long long int ll;

const int INF = 0x3f3f3f3f;
const ll LINF= 0x3f3f3f3f3f3fll;

int main() { _
    int n, z; cin >> n >> z;
    vector<pair<ll,ll>> v;
    while (n--){
        int x; cin >> x;
        v.push_back({x, abs(z-x)});
    }
    ll aux = min(v[0].f, v[0].s);
    ll ans = aux;
    bool c = true;
    for (int i = 1; i < v.size(); i++){
        ll ma = max(v[i].f, v[i].s);
        ll mi = min(v[i].f, v[i].s);
        if(mi >= aux) aux = mi, ans+=aux;
        else if(ma >= aux) aux = ma, ans+=aux;
        else {c = false; break;}
    }
    
    if(c) cout << ans << endl;
    else cout << "-1" << endl;

    return 0;
}