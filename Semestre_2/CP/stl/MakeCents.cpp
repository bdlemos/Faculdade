#include<bits/stdc++.h>

using namespace std;
 
#define _ ios_base::sync_with_stdio(0);cin.tie(0);

int main(){_
    int t ;cin >> t;
    while(t--){
        float ans = 0;
        map<string, float> cur;
        cur["JD"] = 1;
        int c,n; cin >> c >> n;
        for (int i = 0; i < c; i++){
            string s; float val; cin >> s >> val;
            cur[s] = val;
        }
        for (int i = 0; i < n; i++){
            string s; float val; cin >> val >> s;
            ans += cur[s] * val;
        }
        cout << ans<< endl;
    }
    return 0;
}