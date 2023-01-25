#include<bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n';

typedef long long ll;

vector<ll> v;
ll ans;

void sum(int i, int n){
    if(i == 0){
        ans += n/v[i];
        return;
    }
    ll aux = (n/v[i]);
    ans += aux;
    sum(i-1, n - v[i]*aux);
}

int main(){//_
    int n; cin >> n;
    v.resize(n+1,1);
    ans = 0;
    ll index;
    for (int i = 1; i < n; i++){
        v[i] = i * v[i-1];
        if(v[i] > n) {index = i - 1;break;}
    }
    sum(index,n);
    cout <<ans<< endl;;
    return 0;
}