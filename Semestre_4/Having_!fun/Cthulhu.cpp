#include <bits/stdc++.h>

using namespace std;

int times = 0;
vector<vector<int>> adj;
vector<int> visited;
vector<int> parent;
int cycle_start, cycle_end;


void dfs(int v){
    visited[v] = 1;
    for(int i : adj[v]){
        if(visited[i] == 0){
            parent[i] = v;
            dfs(i);
        }else if(visited[i] == 1 && parent[v] != i){
            times++;
        }
    }
    visited[v] = 2;
}

//returns the cycle
vector<int> find_cycle(){
    vector<int> cycle;
    cycle.push_back(cycle_start);
    for(int i = cycle_end; i != cycle_start; i = parent[i]){
        cycle.push_back(i);
    }
    cycle.push_back(cycle_start);
    reverse(cycle.begin(), cycle.end());
    return cycle;
}


int main(){
    int n,m; cin >> n >> m;
    
    adj.resize(n);
    visited.resize(n);
    parent.resize(n);

    for(int i = 0; i < m; i++){
        int a,b; cin >> a >> b; a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    visited.assign(n, 0);
    dfs(0);
    for(int i = 0; i < n; i++){
        if(visited[i] == 0){ 
            cout << "NO\n";
            return 0;
        }
    }
    if(times == 0 or times > 1){
        cout << "NO\n";
        return 0;
    }
    vector<int> cycle = find_cycle();
    cout << "FHTAGN!\n";
    return 0;
}