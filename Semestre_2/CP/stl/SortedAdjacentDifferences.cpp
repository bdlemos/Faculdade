#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main(){
    int t; cin >>t;
    while(t--){
        int n,x; cin >>n;
        multiset<ll> l;
        vector<ll> z, ans;
        for (int i = 0; i < n; i++){cin >> x; l.insert(x);}
        for (auto &&i : l) z.push_back(i);
        for (int i = 0, j = z.size() - 1; i <= j; i++, j--){
            if(i == j) ans.push_back(z[i]);
            else {
                ans.push_back(z[j]);
                ans.push_back(z[i]);
            }
        }
        for (auto i = ans.rbegin(); i != ans.rend() ; i++){
            cout << *i << " ";
        }
        cout << endl;
    }
    return 0;
}