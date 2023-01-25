#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);

typedef long long int ll;

const int INF = 0x3f3f3f3f;
const ll LINF= 0x3f3f3f3f3f3fll;

int main() { _
    int t; cin >> t;
    while (t--){
        ll n, k; cin >> n >> k;
        ll l = 0, r = 1e9;
        while (l < r){
            int m = (l+r)/2;
            if(m <(k-1)/(n-1)) l = m+1;
            else r = m;
        }
        cout << l+k << endl;
    }
    
    return 0;
}