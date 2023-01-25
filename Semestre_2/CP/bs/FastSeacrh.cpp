#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);

typedef long long int ll;

const int INF = 0x3f3f3f3f;
const ll LINF= 0x3f3f3f3f3f3fll;

int main() { _
    int n; cin >>n;
    vector<ll> x;
    for (int i = 0; i < n; i++){
        ll z; cin>>z;
        x.push_back(z);
    }
    sort(x.begin(), x.end());
    for (auto &&i : x)
    {
        cout << i << ' ';
    }
    cout << endl;
    cin >> n;
    while (n--){
        ll y,z; cin >> y >> z;
        auto i = lower_bound(x.begin(),x.end(), y);
        auto j = upper_bound(x.begin(),x.end(), z);
        cout << j - i << endl;;
    }
    
    return 0;
}