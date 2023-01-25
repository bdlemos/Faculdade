#include <bits/stdc++.h>
 
using namespace std;
 
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
 
typedef long long int ll;
 
const int INF = 0x3f3f3f3f;
const ll LINF= 0x3f3f3f3f3f3fll;
 
int main() { _
    int n,m,d; cin >> n >> m >> d;
    vector<int> path(n);
    list<pair<int,int>>plat;
    int max = 0;
    for(int i = 1; i <= m ; i++){
        int x; cin >> x;
        plat.push_back({x,i});
        max+=x;
    }
    if(max + (d-1)*(m+1) < n) { cout << "NO" << endl; return 0; }   
    else cout << "YES" << endl;
    int pos = 0;
    if(d < n){
        bool c = true;
        while (plat.size() and c){
            for (int i = 0; i < plat.front().first; i++){
                if (pos + d + i - 1 < path.size())
                    path[pos + d + i - 1] = plat.front().second;
                else{
                    c = false;
                }
            }
            if(c){
                if(max - plat.front().first > n - (pos + d + plat.front().first -1)) break;
                max -= plat.front().first;  
                pos += d + plat.front().first -1;
                plat.pop_front();
            }
        }
        while (plat.size()){
            for (int i = 0; i < plat.front().first; i++){
                if (pos + i < path.size())
                    path[pos + i] = plat.front().second;
            }
            pos += plat.front().first;
            plat.pop_front();
        }
        
    }else{
        int j = 0;
        while (plat.size()){
            for (int i = 0; i < plat.front().first; i++){
                path[j++] = plat.front().second;
            }
            plat.pop_front();
        }
    }
    
    for (auto &&i : path)
        cout << i << ' ';
    cout << endl;
    return 0;
}