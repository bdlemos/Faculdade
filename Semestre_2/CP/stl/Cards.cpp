#include <bits/stdc++.h>

using namespace std;

int main(){
    char x;
    int n; cin >> n;
    map<char,int> dict;
    for(int i = 0; i < n ; i++) {cin >> x; dict[x]++;}
    int zeros = dict['z'];
    for (int i = 0 ; i < zeros ; i++ ) dict['o']--;
    int ones = dict['o'];
    for (int i = 0; i < ones; i++) cout << 1 << ' ';
    for (int i = 0; i < zeros; i++) cout << 0 << ' ';
    return 0;
}