#include <bits/stdc++.h>
typedef long long ll;
 
using namespace std;
 
int main(){
    string s ;cin >> s;
    vector<char> b;
    int ans = 0;
    for (int i = 0; i < s.size() ; i++){
        if(!b.empty() and s[i] == b.back()){ans++; b.pop_back();}
        else b.push_back(s[i]);
    }
    //cout << ans;
    if(ans % 2) cout << "Yes";
    else cout << "No";
    return 0;
}