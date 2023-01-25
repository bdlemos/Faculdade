#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);

typedef long long int ll;

const int INF = 0x3f3f3f3f;
const ll LINF= 0x3f3f3f3f3f3fll;

string s; 

bool da(int m){
    int count = 1;
    int ans = count;
    for (int i = 0; i < s.size(); i++){
        if(s[i] == 'R') ans = max(ans, count), count = 1;
        else count++;
    }
    if(ans > m) return false;
    else return true;
    
}

int main() { _
    int n; cin >> n;
    while (n--){
        s.clear();
        s += 'R';
        string z;cin >> z;
        s += z + 'R';
        int l = 1, r = 1e6;
        while (l < r){
            int m = (l+r)/2;
            if(!da(m)) l = m+1;
            else r = m;
        }
        cout << l << endl;
    }
    
    return 0;
}