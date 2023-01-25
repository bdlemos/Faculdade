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
        int x; cin >> x;
        ll l1 = pow(2,x), l2 = 0;
        for (int i = 1; i < x/2; i++) l1+= pow(2,i);
        for (int i = x/2; i < x; i++) l2+=pow(2,i);

        cout << abs(l1-l2) << endl;
    }
    return 0;
}