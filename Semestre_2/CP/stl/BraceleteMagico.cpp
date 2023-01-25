#include <bits/stdc++.h>

using namespace std;

int main(){
    int n; cin >> n;
    while (n--){
        string sp, sb; cin >> sp >> sb;
        string rsb; for (auto i = sb.rbegin(); i != sb.rend(); i++) rsb += *i;
        sb += sb;
        rsb += rsb;
        if (rsb.find(sp) != -1 || sb.find(sp) != -1) cout << "S" << endl;
        else cout << "N" << endl;
    }
    return 0;
}