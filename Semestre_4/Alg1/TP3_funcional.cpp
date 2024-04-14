#include <iostream>
#include <vector>
#include <bitset>
#include <string>
using namespace std;

typedef long long ll;
#define maxn 1024

const ll INF = 0x3f3f3f3f3f3f;
const ll MINF = -INF;

vector<vector<ll>> dp(maxn, vector<ll>(maxn, MINF));
vector<vector<pair<ll, short>>> dp2(101, vector<pair<ll, short>>(maxn, {MINF, -1}));
vector<ll> custos(maxn, -1);

vector<pair<ll, ll>> sessoes;
vector<pair<ll, ll>> manobras;
int num_max;

ll calcula_dp(int anterior,int i){
    string ant = bitset<10>(anterior).to_string();
    string at = bitset<10>(i).to_string();
    ll soma = 0;
    ll custo = 0;
    int cont = 0;
    for(int i = ant.size() - 1, j = 0; i >=0; i--, j++){
        int idx_mano = manobras.size() - j - 1;
        if(ant[i] == at[i] and ant[i] == '1') {
            soma += manobras[idx_mano].first/2;
            custo += manobras[idx_mano].second;
            cont++;
        }
        else if (at[i] == '1') {
            soma += manobras[idx_mano].first;
            custo += manobras[idx_mano].second;
            cont++;
        }
    }
    custos[i] = custo;
    return soma*cont;
}

void preenche_dp(){
    int last = sessoes.size() - 1;
    for (int i = 0; i < num_max; i++){
        for(int j = 0; j < num_max; j++){
            dp[i][j] = calcula_dp(i,j);
            if(custos[j] <= sessoes[last].second and sessoes[last - 1].second >= custos[i]){
                if(dp2[last][i].first < dp[i][j]){
                    dp2[last][i].second = j;
                    dp2[last][i].first = dp[i][j];
                }
            }
                
        }
        dp2[last][i].first = dp2[last][i].first * sessoes[last].first;
    }
}

ll solucao(int anterior,int secao){
    if(dp2[secao][anterior].first != MINF) return dp2[secao][anterior].first;
    ll ans = MINF;
    ll index_movimento = MINF;
    for(int i = 0; i < num_max; i++){
        if(custos[i] > sessoes[secao].second) continue;
        ll aux = solucao(i, secao + 1) + dp[anterior][i] * sessoes[secao].first;
        if(ans < aux){
            ans = aux;
            index_movimento = i;
        }
    }
    dp2[secao][anterior].second = index_movimento;
    dp2[secao][anterior].first = ans;
    return dp2[secao][anterior].first;
}

//decodifica o caminho
void decodifica(int i){
    string ant = bitset<10>(i).to_string();
    int cont = 0;
    int cont2 = manobras.size();
    string mano = "";

    for(int i = ant.size() - 1, j = 0; i >=0; i--, j++){
        if(ant[i] == '1') cont ++, mano = to_string(cont2) + " " + mano;
        cont2--;
    }
    cout << cont << " " + mano << endl;
}


void reconstruirCaminho(int secao, int anterior) {
    if (secao == sessoes.size()) return;

    decodifica(dp2[secao][anterior].second);
    reconstruirCaminho(secao + 1, dp2[secao][anterior].second);
}


int main(){
    int num_s, num_m;
    cin >> num_s >> num_m;
    sessoes.resize(num_s);
    manobras.resize(num_m);

    num_max = 1 << num_m;
    for(int i = 0; i < num_s; i++) cin >> sessoes[i].first >> sessoes[i].second; // bonus e tempo
    for(int i = 0; i < num_m ; i++) cin >> manobras[i].first >> manobras[i].second; // pontuacao e tempo
    preenche_dp();
    cout << solucao(0,0) << endl;

    reconstruirCaminho(0, 0);

    return 0;
}