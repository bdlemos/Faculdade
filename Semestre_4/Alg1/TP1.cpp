#include <bits/stdc++.h>

using namespace std;

vector<int> facess(0);
vector<vector<int>> Allfaces(0);

struct Point{
    double x, y;

    Point(): x(0), y(0) {}
    Point(double x, double y): x(x), y(y) {}
    double angularCoefficient(Point a){
        return atan2((a.y - y),(a.x - x));
    }
};


int find(vector<int>& adj, int i){
    for(int j = 0; j < adj.size(); j++){
        if(adj[j] == i) return j;
    }
    return adj.size();
}

void dfs(int v, vector<vector<int>>& adj, set<pair<int,int>>& visited_edges, int father){
    facess.push_back(v);
    int prox = find(adj[v], father);

    if(prox != adj[v].size()){
        if(prox == adj[v].size() - 1) prox = 0;
        else prox++;
        if(visited_edges.find(make_pair(v, adj[v][prox])) == visited_edges.end()){
            visited_edges.insert(make_pair(v, adj[v][prox]));
            dfs(adj[v][prox], adj, visited_edges, v);
        }else{
            if(facess.size() > 2)
                Allfaces.push_back(facess);
            facess.erase(++facess.begin(), facess.end());
        }
    }else{
        for(auto j: adj[v]){
            if(visited_edges.find(make_pair(v, j)) == visited_edges.end()){
                visited_edges.insert(make_pair(v, j));
                dfs(j, adj, visited_edges, v);
            }
        }
    }
}

void face(vector<Point>& vertices, vector<vector<int>>& adj){
    for(int i= 0; i < adj.size(); i++){
        auto cmp = [&](int l, int r) {
            return vertices[i].angularCoefficient(vertices[l]) < vertices[i].angularCoefficient(vertices[r]);
        };
        sort(adj[i].begin(), adj[i].end(), cmp);
    }
    set<pair<int,int>> visited_edges;
    for(int i = 0 ; i < vertices.size(); i++){
        dfs(i, adj, visited_edges, i);
        facess.clear();
    }
    //print adj matrix
    /*
    for(int i = 0; i < adj.size(); i++){
        cout << char(i+97) << ": ";
        for(int j = 0; j < adj[i].size(); j++){
            double aux = vertices[i].angularCoefficient(vertices[adj[i][j]]);
            if(aux < 0) aux += 2*M_PI;
            cout << char(adj[i][j] + 97) << " " << aux*180/M_PI << " | ";
        }
        cout << endl;
    }*/
    return;
}


int main(){
    int num_vertices; cin >> num_vertices;
    int num_edges; cin >> num_edges;
    vector<Point> vertices(num_vertices);
    vector<vector<int>> adj(num_vertices);
    //Preenche a matriz de adjacencia e o vetor de pontos
    for (int i = 0; i < num_vertices; i++){
        cin >> vertices[i].x >> vertices[i].y;
        int grau; cin >> grau;
        for (int j = 0; j < grau; j++){
            int a; cin >> a;
            adj[i].push_back(--a);
        }
    }
    face(vertices, adj);

    cout << Allfaces.size() << endl;
    if(Allfaces.size() != 0){
        for(int j = 0; j < Allfaces.size(); j++){
            cout << Allfaces[j].size() << " ";
            for(int k = 0; k < Allfaces[j].size(); k++){
                //cout << char(Allfaces[j][k] + 97) << " ";
                cout << Allfaces[j][k] + 1 << " ";
            }
            cout << endl;
        }
    } 
    return 0;
}
