#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);

typedef long long int ll;

const int INF = 0x3f3f3f3f;
const ll LINF= 0x3f3f3f3f3f3fll;



int main() { _
    int n; cin >> n;
    ll ans1 = -INF, ans2 = -INF, ans;;
    vector<ll> v(n), d(n,-INF), e(n,-INF);
    for (int i = 0; i < n; i++){
        int x; cin >> v[i];
    }
    d[0] = v[0];
    e[n-1] = v[n-1];
    for (int i = 1; i < n; i++)
        if(v[i] + d[i-1] > v[i]) d[i] = v[i] + d[i-1];
        else d[i] = v[i];
    ll md = d[0], id = 0;
    for (int i = 1; i < n; i++)
        if(d[i] >= md) id = i, md = d[i];
    
    for (int i = v.size() - 2; i >= 0; i--)
        if(e[i] + e[i+1] > 0) e[i] = v[i] + e[i+1];
        else e[i] = v[i];
    int me = e[0], ie = 0;
    for (int i = 1; i < n; i++)
        if(e[i] > me) ie = i, me = e[i];

    if(me == e[0]){
        for (int i = 2; i < n; i++){
            d[1] = v[1];
            if(v[i] + d[i-1] > v[i]) d[i] = v[i] + d[i-1];
            else d[i] = v[i];
        }
        ans2 = (d[n-1] > 0) ? me + d[n-1] : me;
    }else if(me == v[n-1]){
        e[n-2] = v[n-2];
        for (int i = v.size() - 3; i > 0; i--)
            if(v[i] + e[i+1] > v[i]) e[i] = v[i] + e[i+1];
            else e[i] = v[i];
        ans2 = (e[0] > 0) ? me + e[0] : me;
    }else{
        ans2 = me;
    }

    if(md == d[0]){
        for (int i = 2; i < n; i++){
            d[1] = v[1];
            if(v[i] + d[i-1] > v[i]) d[i] = v[i] + d[i-1];
            else d[i] = v[i];
        }
        ans = (d[n-1] > 0) ? md + d[n-1] : md;
    }else if(md == d[n-1]){
        e[n-2] = v[n-2];
        for (int i = v.size() - 3; i > 0; i--)
            if(v[i] + e[i+1] > v[i]) e[i] = v[i] + e[i+1];
            else e[i] = v[i];
        ans = (e[0] > 0) ? md + e[0] : md;
    }else{
        ans = md;
    }
    if(ans < 0) ans = 0;
    /*for (auto &&i : d)
        cout << i << ' ';
    cout << endl;
    for (auto &&i : e)
        cout << i << ' ';
    */
    cout <<max(ans,ans2) <<endl;
    return 0;
}