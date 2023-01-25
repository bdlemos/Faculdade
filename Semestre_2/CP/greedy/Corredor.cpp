#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);

typedef long long int ll;

const int INF = -0x3f3f3f3f;
const ll LINF= -0x3f3f3f3f3f3fll;

int main() { _
    int n; cin >> n;
    vector<int> l;
    while (n--) {
        int x; cin >> x; 
        l.push_back(x);
    }
    int ans = INF;
    int z = INF;
    for (auto i : l){
        if (ans + i < i) {ans = i;}
        else ans += i;
        z = max(z,ans);
    }
    cout << z << endl;
    return 0;
}