#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main(){
    int n; cin >> n;
    vector<pair<int,int>> v(61, {0,0});
    int ans = 0;
    while (n--){
        int size; 
        char pe;
        cin >> size >> pe;
        if(pe == 'E') v[size].first++;
        else v[size].second++;
    }
    for (auto &&i : v) ans += min(i.first,i.second);
    cout << ans << endl;
}
