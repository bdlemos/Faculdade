#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);

typedef long long int ll;

const int INF = 0x3f3f3f3f;
const ll LINF= 0x3f3f3f3f3f3fll;

int main() { _
    int n,k; cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    for (int i = 0; i < k; i++) {
        int l = 0, r = n, z;
        cin >> z;
        while(l < r){
            int m = (l+r)/2;
            if(a[m] < z) l = m+1;
            else r=m;
        }
        string ans = a[l] == z ? "YES" : "NO";
        cout << ans << endl;
    }
    return 0;
}