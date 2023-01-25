#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define f first
#define s second

typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

int main() { //_
    int n; cin >> n;
    while (n--){
        ll x; cin >> x;
        int v, l; cin >> v >> l;
        while (v > 0 && x > x/2 + 10){
                v--;
                x = x/2 + 10;
        }
        x -= 10*l;
        if(x <= 0) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    
    
    return 0;
}