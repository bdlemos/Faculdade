#include <bits/stdc++.h>

const int INF = 1000000000;

using namespace std;

vector<pair<int,int>> conjuntos;
vector<bool> visited;
vector<int> parent;

struct info{
    int year, dist, price;
};

// DSU
void make_set(){
    for (int i = 0; i < conjuntos.size(); i++) conjuntos[i] = make_pair(i, 1);
}

pair<int,int> find(int i){
    if(i != conjuntos[i].first){
        conjuntos[i] = find(conjuntos[i].first);
    }
    return conjuntos[i];
}


void Union(int a, int b){
    if(find(a).second < find(b).second) Union(b,a);
    auto z = find(a), x = find(b);
    conjuntos[x.first] = make_pair(z.first, z.second + x.second);
    conjuntos[z.first].second = z.second + x.second;
}
// end DSU


vector<pair<pair<int,int>,info>> flatten(vector<vector<pair<int,info>>> adj){
    vector<pair<pair<int,int>,info>> aux;
    for (int i = 0; i < adj.size(); i++){
        for (int j = 0; j < adj[i].size(); j++){
            aux.push_back(make_pair(make_pair(i,adj[i][j].first), adj[i][j].second));
        }
    }
    return aux;
}

vector<int> dijkstra_distancia(vector<vector<pair<int,info>>> adj, int vertice){
    visited.assign(adj.size(),false);
    vector<int> dist(adj.size(),INF);
    
    dist[vertice] = 0;
    parent[vertice] = vertice;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push(make_pair(0, vertice));

    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();
        if (visited[u]) continue;
        visited[u] = true;
        
        for(auto n: adj[u]){
            if(visited[n.first]) continue;
            
            int v = n.first;
            auto w = n.second;
            if(dist[v] > dist[u] + w.dist){
                parent[v] = w.year;
                dist[v] = dist[u] + w.dist;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    return dist;
}

//Faz o kruskal e printa o ano maximo
void kruskal_year(vector<pair<pair<int,int>,info>> adj){
    make_set();

    sort(adj.begin(), adj.end(), [](const pair<pair<int,int>,info> &a, const pair<pair<int,int>,info> &b){
        return a.second.year < b.second.year;
    });
    int max = -1;
    for(auto i: adj){
        pair<pair<int,int>,info> aux = i;
        if(find(aux.first.first) != find(aux.first.second)){
            Union(aux.first.first, aux.first.second);
            if(aux.second.year > max) max = aux.second.year;
        }
    }
    cout << max << endl;
}

//Faz o kruskal e printa o custo minimo
void kruskal_price(vector<pair<pair<int,int>,info>> adj){
    make_set();
    int custo = 0;
    sort(adj.begin(), adj.end(), [](const pair<pair<int,int>,info> &a, const pair<pair<int,int>,info> &b){
        return a.second.price < b.second.price;
    });
    for(auto i: adj){
        pair<pair<int,int>,info> aux = i;
        if(find(aux.first.first) != find(aux.first.second)){
            Union(aux.first.first, aux.first.second);
            custo += aux.second.price;
        }
    }
    cout << custo << endl;
}

int main(){
    int num_vertices; cin >> num_vertices;
    int num_edges; cin >> num_edges;

    // Cria a matriz de adjacencia
    vector<vector<pair<int,info>>> adj(num_vertices);
    conjuntos.resize(num_vertices);
    parent.resize(num_vertices);
    visited.resize(num_vertices);

    //Preenche a matriz de adjacencia
    for (int i = 0; i < num_edges; i++){
        int a,b; cin >> a >> b;
        
        int year, dist, price;
        cin >> year >> dist >> price;

        info aux = {year, dist, price};
        adj[a-1].push_back(make_pair(b-1, aux));
        adj[b-1].push_back(make_pair(a-1, aux));

    }

    vector<int> dist = dijkstra_distancia(adj, 0);
    for(auto i: dist) cout << i << '\n';
    cout << *max_element(parent.begin(), parent.end()) << endl;
    
    auto adj1 = flatten(adj);
    kruskal_year(adj1);
    kruskal_price(adj1);
    return 0;
}
