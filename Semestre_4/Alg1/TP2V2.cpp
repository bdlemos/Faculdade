#include <bits/stdc++.h>

const long long INF = 10e12;
typedef long long ll;

using namespace std;

vector<pair<ll,ll>> conjuntos;
vector<bool> visited;
vector<ll> parent;

struct info{
    ll year, dist, price;
};

// DSU
void make_set(){
    for (ll i = 0; i < conjuntos.size(); i++) conjuntos[i] = make_pair(i, 1);
}

pair<ll,ll> find(ll i){
    if(i != conjuntos[i].first){
        conjuntos[i] = find(conjuntos[i].first);
    }
    return conjuntos[i];
}


void Union(ll a, ll b){
    if(find(a).second < find(b).second) Union(b,a);
    auto z = find(a), x = find(b);
    conjuntos[x.first] = make_pair(z.first, z.second + x.second);
    conjuntos[z.first].second = z.second + x.second;
}
// end DSU


vector<pair<pair<ll,ll>,info>> flatten(vector<vector<pair<ll,info>>> adj){
    vector<pair<pair<ll,ll>,info>> aux;
    for (ll i = 0; i < adj.size(); i++){
        for (ll j = 0; j < adj[i].size(); j++){
            aux.push_back(make_pair(make_pair(i,adj[i][j].first), adj[i][j].second));
        }
    }
    return aux;
}

//Questao 1
//Dijkstra para calcular a distancia minima e salva o custo de cada aresta usada no vetor "parent"
vector<ll> dijkstra_distancia(vector<vector<pair<ll,info>>> adj, ll vertice){
    visited.assign(adj.size(),false);
    vector<ll> dist(adj.size(),INF);
    
    dist[vertice] = 0;
    parent[vertice] = vertice;
    
    //PQ é uma fila de prioridade que é ordenada pela distancia acumulada e o desempate é o tempo da aresta, 
    //por isso o primeiro elemento de cada par é um par, onde o primeiro é
    // a distancia e o segundo é o tempo da ultima aresta
    priority_queue<pair<pair<ll,ll>,ll>, vector<pair<pair<ll,ll>,ll>>, greater<pair<pair<ll,ll>,ll>>> pq;
    pq.push(make_pair(make_pair(0,0), vertice));

    while(!pq.empty()){
        auto peso = pq.top().first;
        ll u = pq.top().second;
        pq.pop();
        if (visited[u]) continue;

        visited[u] = true;
        dist[u] = peso.first;
        parent[u] = peso.second;
        
        for(auto n: adj[u]){
            if(visited[n.first]) continue;
            
            ll v = n.first;
            auto w = n.second;
            if(dist[v] > dist[u] + w.dist){
                pq.push(make_pair(make_pair(dist[u] + w.dist,w.year), v));
            }
        }
    }
    return dist;
}

//Faz o kruskal e printa o ano maximo
void kruskal_year(vector<pair<pair<ll,ll>,info>> adj){
    make_set();

    sort(adj.begin(), adj.end(), [](const pair<pair<ll,ll>,info> &a, const pair<pair<ll,ll>,info> &b){
        return a.second.year < b.second.year;
    });
    ll max = -1;
    for(auto i: adj){
        pair<pair<ll,ll>,info> aux = i;
        if(find(aux.first.first) != find(aux.first.second)){
            Union(aux.first.first, aux.first.second);
            if(aux.second.year > max) max = aux.second.year;
        }
    }
    cout << max << endl;
}

//Faz o kruskal e printa o custo minimo
void kruskal_price(vector<pair<pair<ll,ll>,info>> adj){
    make_set();
    ll custo = 0;
    sort(adj.begin(), adj.end(), [](const pair<pair<ll,ll>,info> &a, const pair<pair<ll,ll>,info> &b){
        return a.second.price < b.second.price;
    });
    for(auto i: adj){
        pair<pair<ll,ll>,info> aux = i;
        if(find(aux.first.first) != find(aux.first.second)){
            Union(aux.first.first, aux.first.second);
            custo += aux.second.price;
        }
    }
    cout << custo << endl;
}

int main(){
    ll num_vertices;
    ll num_edges;
    scanf("%lld", &num_vertices);
    scanf("%lld", &num_edges);

    // Cria a matriz de adjacencia
    vector<vector<pair<ll,info>>> adj(num_vertices);
    conjuntos.resize(num_vertices);
    parent.resize(num_vertices);
    visited.resize(num_vertices);

    //Preenche a matriz de adjacencia
    for (ll i = 0; i < num_edges; i++){
        ll a,b; scanf("%lld%lld", &a,&b);
        
        ll year, dist, price; scanf("%lld%lld%lld", &year, &dist, &price);

        info aux = {year, dist, price};
        adj[a-1].push_back(make_pair(b-1, aux));
        adj[b-1].push_back(make_pair(a-1, aux));

    }

    vector<ll> dist = dijkstra_distancia(adj, 0);
    for(auto i: dist) cout << i << '\n';
    cout << *max_element(parent.begin(), parent.end()) << endl;
    
    auto adj1 = flatten(adj);
    kruskal_year(adj1);
    kruskal_price(adj1);
    return 0;
}
