#include <bits/stdc++.h>

using namespace std;

int times = 0;

void dfs(int v, vector<vector<int>>& adj, vector<int>& visited){
    visited[v] = 1;
    for(int i : adj[v]){
        if(visited[i] == 0){
            dfs(i, adj, visited);
        }
    }
}

int main(){
    int n,m; cin >> n >> m;
    vector<vector<int>> adj(n+1);
    for(int i = 0; i < m; i++){
        int a,b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> visited(n+1, 0);
    for (int i = 1; i < n+1; i++){
        if(visited[i] == 0){
            dfs(i, adj, visited);
            times++;
        }
    }
    cout << times << endl;
    return 0;
}