#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);

typedef long long int ll;

const int INF = 0x3f3f3f3f;
const ll LINF= 0x3f3f3f3f3f3fll;

int main() { //_
    int n, k; cin >> n >> k;
    int cont = 0;
    vector<int> arr(n);
    for (int i = 0; i < n; i++){
        int x; cin >> x;
        arr[i] = x;
    }
    for (int i = 0; i < n; i++){
        if(arr[i] > 0 and arr[i] >= arr[k-1]) cont++;
    }
    cout << cont;
    return 0;
}