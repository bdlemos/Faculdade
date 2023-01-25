#include <bits/stdc++.h>

#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f
#define pii pair<int, int>
#define _ ios_base::sync_withstdio(0);cin.tie(0);

using namespace std;
typedef long long int ll;

bool cmp(string a, string b){
    if(a.size() < b.size()) return true;
    if(a < b && a.size() == b.size()) return true;
    return false;
}

int main() {
    string s2;
    vector<string> v;
    while (cin >> s2){
        if(s2[s2.size()-1] < 'A' or s2[s2.size()-1] > 'z') s2[s2.size()-1] = ' ';
        if (s2.size() == 1 and s2[s2.size()-1] < 'A' or s2[s2.size() - 1] > 'z') continue;
        else transform(s2.begin(), s2.end(), s2.begin(), ::tolower), v.push_back(s2);
    }
    sort(v.begin(), v.end(), cmp);
    for (auto &&i : v)
        cout << i << endl;
    return 0;
}