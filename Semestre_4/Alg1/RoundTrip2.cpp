#include <bits/stdc++.h>
using namespace std;
 
const int MAX = 1e6;
 
vector<vector<int>> t(MAX);
vector<int> visited(MAX);
vector<int> parent(MAX);
int cycleStart, cycleEnd;
int n,m; 
 
bool dfs(int v){
    visited[v] = 1;
    for(auto u: t[v]){
        if(visited[u] == 0 and dfs(u)){
            parent[u] = v;
            return true;
        }
        if (visited[u] == 1) {
            cycleEnd = v;
            cycleStart = u;
            return true;
        }
    }
    visited[v]= 2;
    return false;
}
 
void find_cycle(){
    visited.assign(n, 0);
    parent.assign(n, -1);
    cycleStart = -1;
 
    for (int v = 0; v < n; v++) {
        if (!visited[v] && dfs(v))
            break;
    }
 
    if (cycleStart == -1) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        vector<int> cycle;
        cycle.push_back(cycleStart);
        for (int v = cycleEnd; v != cycleStart; v = parent[v])
            cycle.push_back(v);
        cycle.push_back(cycleStart);
 
        cout << cycle.size() << endl;
        for (auto i = cycle.rbegin(); i!= cycle.rend(); i++)
            cout << *i << " ";
        cout << endl;
    }
    
}
 
int main(){
    cin >> n >> m;
    while (m > 0){
        int i,j; cin >> i >>j;
        t[i].push_back(j);
        m--;
    }
    find_cycle();
    return 0;
}