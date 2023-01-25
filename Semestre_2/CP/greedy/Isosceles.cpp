#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);

typedef long long int ll;

const int INF = 0x3f3f3f3f;
const ll LINF= 0x3f3f3f3f3f3fll;



int main() { _
    int n; cin >> n;
    int ans = -INF;
    vector<int> v(n), d(n,1), e(n,1);
    for (int i = 0; i < n; i++){
        int x; cin >> v[i];
    }
    for (int i = 1; i < n; i++)
        if(v[i] > d[i-1]) d[i] += d[i-1];
        else d[i] = v[i];
    for (int i = v.size() - 2; i >= 0; i--)
        if(v[i] > e[i+1]) e[i] += e[i+1];
        else e[i] = v[i];
    for (int i = 0; i < n; i++)
        ans = max(ans, min(d[i],e[i]));
    cout <<ans <<endl;
    return 0;
}