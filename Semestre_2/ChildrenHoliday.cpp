#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);

typedef long long int ll;

const int INF = 0x3f3f3f3f;
const ll LINF= 0x3f3f3f3f3f3fll;

struct T{
    ll x;
    ll y;
    ll z;
};

int b, a;
vector<T> t;

bool da(ll m){
    int aux = b;
    for(int i = 0; i < a; i++){
        ll time = 0;
        while(1){
            time += (t[i].x*t[i].y);
            if(time > m) break;
            aux -= t[i].y;
            if(aux > 0) time+=t[i].z;
            else return true;
        }
    }
    if(aux <= 0) return true;
    else return false;
}

void prints(ll m){
    int aux = b;
    for(int i = 0; i < a; i++){
        ll time = 0;
        while(1){
            time += (t[i].x*t[i].y);
            if(time > m) break;
            aux -= t[i].y;
            if(aux > 0) time+=t[i].z;
            else break;
        }
            cout << b - aux<< ' ';
    }
}

int main() { //_
    cin >> b >> a;
    for (int i = 0; i < a; i++){
        int x,y,z; cin >> x >> y >> z;
        t.push_back({x,y,z});
    }
    
    ll l= 1, r = 100*100*15000;
    while(l < r){
        ll m = (l+r)/2;
        if(!da(m)) l = m + 1;
        else r = m;
    }
    cout << l << endl;
    prints(l);
    cout << endl;
    
    return 0;
}