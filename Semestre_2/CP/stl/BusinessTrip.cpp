#include<bits/stdc++.h>

using namespace std;

int main(){
    int k, v; cin >> k;
    multiset<int> l;
    for (int i = 0; i < 12; i++){cin >> v; l.insert(v);}
    int s = 0, z = 0;
    if(!k) z = 0;
    else{ 
        bool c = false;
        for (auto i = l.rbegin(); i != l.rend(); i++) {
        s+= *i;
        z++;
        if(s >= k) {c = true; break;};
        }
        if(!c) z = -1;
    }
    cout << z << endl;
    
}