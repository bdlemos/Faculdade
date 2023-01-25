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
    map<string,int> l;
    map<int,string> a;
 
    while(n--){
        string name; cin >> name;
        l[name] = n;
    }
    for (auto &&i : l) a[i.second] = i.first;
    for (auto &&i : a) cout << i.second << endl;
    
    return 0;
}