#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);

typedef long long int ll;

const int INF = 0x3f3f3f3f;
const ll LINF= 0x3f3f3f3f3f3fll;

int main() { _
    int n, m; cin >> n >> m;
    vector<int> v;
    while (n--){
        int x; cin >> x;
        v.push_back(x);
    }
    int ans = 0;
    for (int i = 0; i < v.size() - 1; i++){
        if (v[i] != m){
            ans += abs(v[i] - m);
            v[i+1] -= v[i] - m;
        }
        
    }

    cout << ans << endl;
    
    return 0;
}