#include <bits/stdc++.h>
using namespace std;
 
const int MAX = 1e6;
 
vector<vector<int>> t(MAX);
vector<bool> visited(MAX);
vector<int> parent(MAX);
int cycleStart, cycleEnd;
int n,m; 
 
bool dfs(int v, int par){
    visited[v] = true;
    for(auto u: t[v]){
        if(u == par) continue; // skipping edge to parent vertex
        if (visited[u]) {
            cycleEnd = v;
            cycleStart = u;
            return true;
        }
        parent[u] = v;
        if (dfs(u, parent[u]))
            return true;
    }
    return false;
}
 
void find_cycle(){
    visited.assign(n, false);
    parent.assign(n, -1);
    cycleStart = -1;
 
    for (int v = 0; v < n; v++) {
        if (!visited[v] && dfs(v, parent[v]))
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
        for (int v : cycle)
            cout << v << " ";
        cout << endl;
    }
    
}
 
int main(){
    cin >> n >> m;
    while (m > 0){
        int i,j; cin >> i >>j;
        t[i].push_back(j);
        t[j].push_back(i);
        m--;
    }
    find_cycle();
    return 0;
}