#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n';

typedef long long int ll;

const int INF = 0x3f3f3f3f;
const ll LINF= 0x3f3f3f3f3f3fll;

int main() { _
    set<pair<int,int>> order;
    int n;
    cin >> n;
    while (n--){
        ll s, e; cin >> s >> e;
        order.insert({e,s});
    }
    int ans = 1, aux = order.begin()->first;
    for (auto &&i : order){
        if(i.second > aux) ans++, aux = i.first;
    }
    cout << ans << endl;
    return 0;
}