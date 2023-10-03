#include <bits/stdc++.h>

using namespace std;

int times = -1, aux = -1, vertice;
vector<vector<int>> adj;
vector<int> visited;


void dfs(int v){
    times++;
    visited[v] = 1;
    for(int i : adj[v]){
        if(visited[i] == 0){
            dfs(i);
        }
    }
    if(times > aux){
        aux = times;
        vertice = v;
    }
    times--;
    visited[v] = 2;
}


int main(){
    int n; cin >> n;
    
    adj.resize(n);
    visited.resize(n);
    visited.assign(n, 0);
    for(int i = 0; i < n-1; i++){
        int a,b; cin >> a >> b; a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(0);
    visited.assign(n, 0);
    dfs(vertice);
    cout << aux<< "\n";
    return 0;
}