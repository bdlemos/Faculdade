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
    set<string> ov;
    string s2;
    while (cin >> s2){
        if(s2[s2.size()-1] < 'A' or s2[s2.size()-1] > 'z') s2[s2.size()-1] = ' ';
        if (s2.size() == 1 and s2[s2.size()-1] < 'A' or s2[s2.size() - 1] > 'z') continue;
        else transform(s2.begin(), s2.end(), s2.begin(), ::tolower), ov.insert(s2);
    }
    for (auto &&i : ov)cout << i << endl;
    
    
    return 0;
}