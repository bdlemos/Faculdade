#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define f first
#define s second

typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

int main() { _
    int n; cin >> n;
    while (n--){
        ll x, y; cin >> x >> y;
        ll a, b; cin >> a >> b;
        ll m = max(x,y) - min(x,y);
        ll ans = 0;
        double ca = b/double(a);
        //cout << ca << endl;
        if (ca > 2) {
            ans += (m*a);
            ans += 2*(min(x,y)*a);
        }
        else {
            m *= a;
            ans += m;
            ans += min(x,y)*b;
        }
        cout << ans<< endl;
    }
    return 0;
}