#include <bits/stdc++.h>

using namespace std;

int n;
vector<vector<int>> adj, adj_t;
vector<bool> used;
vector<int> order, comp;
vector<bool> assignment;

void dfs1(int v) {
    used[v] = true;
    for (int u : adj[v]) {
        if (!used[u])
            dfs1(u);
    }
    order.push_back(v);
}

void dfs2(int v, int cl) {
    comp[v] = cl;
    for (int u : adj_t[v]) {
        if (comp[u] == -1)
            dfs2(u, cl);
    }
}

bool solve_2SAT() {
    order.clear();
    used.assign(2*n, false);
    for (int i = 0; i < 2*n; ++i) {
        if (!used[i])
            dfs1(i);
    }

    comp.assign(2*n, -1);
    for (int i = 0, j = 0; i < 2*n; ++i) {
        int v = order[2*n - i - 1];
        if (comp[v] == -1)
            dfs2(v, j++);
    }

    assignment.assign(n, false);
    for (int i = 0; i < 2*n; i += 2) {
        if (comp[i] == comp[i + 1])
            return false;
        assignment[i / 2] = comp[i] > comp[i + 1];
    }
    return true;
}

void add_disjunction(int a, bool na, int b, bool nb) {
    // na and nb signify whether a and b are to be negated 
    a = 2*a ^ na;
    b = 2*b ^ nb;
    int neg_a = a ^ 1;
    int neg_b = b ^ 1;
    adj[neg_a].push_back(b);
    adj[neg_b].push_back(a);
    adj_t[b].push_back(neg_a);
    adj_t[a].push_back(neg_b);
}

int main(){
    int m; cin >> m >> n;
    adj.resize(2*n);
    adj_t.resize(2*n);
    for(int i = 0; i < m; i++){
        char a,b; int a1,b1; cin >> a >> a1 >> b >> b1;
        bool flags[2];
        if (a == '+') flags[0] = true;
        else flags[0] = false;
        if (b == '+') flags[1] = true;
        else flags[1] = false;
        add_disjunction(a1-1, flags[0], b1-1, flags[1]);
    }
    if(solve_2SAT()){
        for(int i = 0; i < n; i++){
            if(assignment[i]) cout << "- ";
            else cout << "+ ";
        }
        cout << endl;
    }
    else{
        cout << "IMPOSSIBLE" << endl;
    }
    return 0;
}