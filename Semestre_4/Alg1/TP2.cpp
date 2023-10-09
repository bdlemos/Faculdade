#include <bits/stdc++.h>

const int INF = 1000000000;

using namespace std;

vector<int> parent;
vector<bool> visited;

struct info{
    int year, dist, price;
};


int sum (vector<int> v){
    int sum = 0;
    for (int i = 0; i < v.size(); i++){
        sum += v[i];
    }
    return sum;
}


//Questao 1
//Dijkstra para calcular a distancia minima e salva o custo de cada aresta usada no vetor "parent"
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

//Questao 2
//Prim para calcular o menor tempo possivel e salva o tempo de cada aresta percorrida no vetor "year" e o retorna
vector<int> Prim_Year(vector<vector<pair<int,info>>> adj, int vertice){

    int maior = -1;
    visited.assign(adj.size(),false);
    vector<int> year(adj.size(),INF);


    year[vertice] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push(make_pair(0, vertice));

    while(!pq.empty()){
        int edge_year = pq.top().first; // ano da aresta
        int u = pq.top().second; // vertice
        pq.pop();

        if (visited[u]) continue;
        
        if(edge_year > maior) maior = edge_year; // salva o maior ano percorrido
        year[u] = edge_year; // salva o ano da aresta no vertice destino
        visited[u] = true;

        for(auto n: adj[u]){
            if (visited[n.first]) continue;
            int v = n.first;
            auto w = n.second;
            pq.push(make_pair(w.year, v));
            }
    }
    cout << maior << endl;
    return year;
}


//Questao 3
//Prim para calcular o menor preco possivel de cada vertice e salva o preco de cada aresta percorrida no vetor "price" e o retorna
vector<int> Prim_Price(vector<vector<pair<int,info>>> adj, int vertice){
    int sum = 0;
    visited.assign(adj.size(),false);
    vector<int> price(adj.size(),INF);


    price[vertice] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push(make_pair(0, vertice));

    while(!pq.empty()){
        int edge_price = pq.top().first; // preco da aresta
        int u = pq.top().second; // vertice
        pq.pop();

        if (visited[u]) continue;

        sum += edge_price; // salva o preço total
        price[u] = edge_price; // salva o preco da aresta no vertice destino
        visited[u] = true;

        for(auto n: adj[u]){
            if (visited[n.first]) continue;
            int v = n.first;
            auto w = n.second;
            pq.push(make_pair(w.price, v));
            }
    }
    cout << sum << endl;
    return price;
}


int main(){
    int num_vertices; cin >> num_vertices;
    int num_edges; cin >> num_edges;

    // Cria a matriz de adjacencia
    vector<vector<pair<int,info>>> adj(num_vertices);
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

    //Pergunta 1
    vector<int> dist = dijkstra_distancia(adj, 0);
    for(auto i: dist){
        cout << i << '\n';
    }

    //Pergunta 1a

    cout << *max_element(parent.begin(), parent.end()) << endl;

    //Pergunta 2
    vector<int> year = Prim_Year(adj, 0);
    //print parent
    //cout << *max_element(year.begin(), year.end()) << endl;

    //Pergunta 3
    vector<int> price = Prim_Price(adj, 0);
    //cout << sum(price) << endl;
    return 0;
}
