#include<bits/stdc++.h>

using namespace std;

int main(){
    int n, x; cin >> n;
    
    set<int> A;
    for (int i = 0; i < n; i++) {cin >> x; A.insert(x);}
    int m; cin >> m;
    set<int> B;
    for (int i = 0; i < m; i++) {cin >> x; B.insert(x);}
    cout << *(A.rbegin()) << " " << *(B.rbegin()) << endl;
}