#include <bits/stdc++.h>

typedef long long ll;
const ll INF = 10e12;

using namespace std;

vector<ll> parent;
vector<bool> visited;

struct info{
    ll year, dist, price;
};

//Questao 1
//Dijkstra para calcular a distancia minima e salva o custo de cada aresta usada no vetor "parent"
vector<ll> dijkstra_distancia(vector<vector<pair<ll,info>>> adj, ll vertice){
    visited.assign(adj.size(),false);
    vector<ll> dist(adj.size(),INF);
    
    dist[vertice] = 0;
    parent[vertice] = vertice;
    
    //PQ é uma fila de prioridade que é ordenada pela distancia e o desempate é o tempo da aresta, por isso o primeiro elemento de cada par é um par, onde o primeiro é
    // a distancia e o segundo é o tempo da ultima aresta
    priority_queue<pair<pair<ll,ll>,ll>, vector<pair<pair<ll,ll>,ll>>, greater<pair<pair<ll,ll>,ll>>> pq;
    pq.push(make_pair(make_pair(0,0), vertice));

    while(!pq.empty()){
        auto peso = pq.top().first;
        ll u = pq.top().second;
        pq.pop();

        if(dist[u] == peso.first) (parent[u] > peso.second) ? parent[u] = peso.second : parent[u] = parent[u];
        if (visited[u]) continue;
        
        visited[u] = true;
        
        // peso.first = distancia e peso.second = tempo da aresta do pai para o vertice atual
        dist[u] = peso.first;
        parent[u] = peso.second;
        
        for(auto n: adj[u]){
            //if(visited[n.first]) continue;
            
            ll v = n.first;
            auto w = n.second;
            if(dist[v] >= dist[u] + w.dist){
                dist[v] = dist[u] + w.dist;
                pq.push(make_pair(make_pair(dist[u] + w.dist,w.year), v));
            }
        }
    }
    return dist;
}

//Questao 2
//Prim para calcular o menor tempo possivel e salva o tempo de cada aresta percorrida no vetor "year" e o retorna
void Prim_Year(vector<vector<pair<ll,info>>> adj, ll vertice){

    ll maior = -1;
    visited.assign(adj.size(),false);
    //vector<ll> year(adj.size(),INF);


    //year[vertice] = 0;
    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq;
    pq.push(make_pair(0, vertice));

    while(!pq.empty()){
        ll edge_year = pq.top().first; // ano da aresta
        ll u = pq.top().second; // vertice
        pq.pop();

        if (visited[u]) continue;
        
        if(edge_year > maior) maior = edge_year; // salva o maior ano percorrido
        //year[u] = edge_year; // salva o ano da aresta no vertice destino
        visited[u] = true;

        for(auto n: adj[u]){
            if (visited[n.first]) continue;
            ll v = n.first;
            auto w = n.second;
            pq.push(make_pair(w.year, v));
            }
    }
    cout << maior << endl;
    //return year;
}


//Questao 3
//Prim para calcular o menor preco possivel de cada vertice e salva o preco de cada aresta percorrida no vetor "price" e o retorna
void Prim_Price(vector<vector<pair<ll,info>>> adj, ll vertice){
    ll sum = 0;
    visited.assign(adj.size(),false);
    //vector<ll> price(adj.size(),INF);


   //price[vertice] = 0;
    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq;
    pq.push(make_pair(0, vertice));

    while(!pq.empty()){
        ll edge_price = pq.top().first; // preco da aresta
        ll u = pq.top().second; // vertice
        pq.pop();

        if (visited[u]) continue;

        sum += edge_price; // salva o preço total
        //price[u] = edge_price; // salva o preco da aresta no vertice destino
        visited[u] = true;

        for(auto n: adj[u]){
            if (visited[n.first]) continue;
            ll v = n.first;
            auto w = n.second;
            pq.push(make_pair(w.price, v));
            }
    }
    cout << sum << endl;
    //return price;
}


int main(){
    ll num_vertices;
    ll num_edges;
    scanf("%lld", &num_vertices);
    scanf("%lld", &num_edges);

    // Cria a matriz de adjacencia
    vector<vector<pair<ll,info>>> adj(num_vertices);
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

    //Pergunta 1
    vector<ll> dist = dijkstra_distancia(adj, 0);
    for(auto i: dist){
        cout << i << '\n';
    }

    //Pergunta 1a

    cout << *max_element(parent.begin(), parent.end()) << endl;

    //Pergunta 2
    //vector<ll> year = Prim_Year(adj, 0);
    Prim_Year(adj, 0);
    //prll parent
    //cout << *max_element(year.begin(), year.end()) << endl;

    //Pergunta 3
    //vector<ll> price = Prim_Price(adj, 0);
    Prim_Price(adj, 0);
    //cout << sum(price) << endl;
    return 0;
}
