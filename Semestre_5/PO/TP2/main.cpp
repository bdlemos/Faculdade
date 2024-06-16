#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>

#define MAX_SIZE 10e3



using namespace std;

const double MIN = numeric_limits<double>::lowest();
const double EPSILON = 1e-6;

vector<vector<double>> tableau1(MAX_SIZE, vector<double>(MAX_SIZE,0)); // Auxiliar
vector<vector<double>> tableau2(MAX_SIZE, vector<double>(MAX_SIZE,0)); // Principal
int tamanho_real_col_principal;
int tamanho_real_col_auxiliar;
bool existe_sol = false;
bool ilimitado = false;
int coluna_ilimitada;
vector<int> base_inicial;
int n, m;

void Monta_tableau_principal(){
    tamanho_real_col_principal = n+m+1;

    //As primeiras n colunão serão do tablo extendido
    //Matriz identidade e vetor de zeros
    for (int i = 0; i < n; i++) tableau2[i+1][i] = 1;


    // Lê o vetor custo
    //Primeira linha
    for (int i = n; i < n+m; i++) cin >> tableau2[0][i], tableau2[0][i]*=-1;

    // Lê as restrições
    for (int i = 1; i < n+1; i++){
        for (int j = n; j < tamanho_real_col_principal; j++){
            cin >> tableau2[i][j];
        }

        //Trata a restrição/linha quando o b é negativo
        if(tableau2[i][tamanho_real_col_principal-1] < 0){
            for (int j = n; j < tamanho_real_col_principal; j++)
                tableau2[i][j] *= -1;
        }
    }
}

void Monta_tableau_auxiliar(){
    int num_aux_var = n;
    tamanho_real_col_auxiliar = n+m+num_aux_var+1;

    //As primeiras n colunão serão do tablo extendido
    //Matriz identidade e vetor de zeros
    for (int i = 0; i < n; i++) tableau1[i+1][i] = 1;


    //Seta o vetor custo
    for (int i = n+m, j=1; i < tamanho_real_col_auxiliar-1; i++,j++) {
        tableau1[0][i] = 1;
    }

    // Copia as restriçoes
    for (int i = 1; i < n+1; i++){
        for (int j = n; j < n+m; j++){
            tableau1[i][j] = tableau2[i][j];
        }
    }

    //Adiciona as variaveis auxiliares nas restriçoes(identidade)
    for (int i = n+m, j=1; i < tamanho_real_col_auxiliar-1; i++,j++) tableau1[j][i] = 1;
    
    // Copia o vetor b;
    for (int i = 1; i < n+1; i++) tableau1[i][tamanho_real_col_auxiliar-1] = tableau2[i][tamanho_real_col_principal-1];
}

void print_principal(){
    for (int i = 0; i < n+1; i++){
        for (int j = 0; j < tamanho_real_col_principal; j++){
            cout << setw(6)<< setprecision(3) <<tableau2[i][j] << ' ';
        }
        cout << endl;
    }
    
    cout << endl;
}

void print_auxiliar(){
    for (int i = 0; i < n+1; i++){
        for (int j = 0; j < tamanho_real_col_auxiliar; j++){
            cout << setw(6) << setprecision(3) <<tableau1[i][j] << ' ';
        }
        cout << endl;
    }
    
    cout << endl;
}

// Realiza a operação de pivotamento na matriz tableau com o objetivo de zerar todos os elementos da coluna do pivô, exceto o próprio pivô
// Trata erro de precisão de ponto flutuante
void pivotTableau(int pivotRow, int pivotCol, int tablo) {
    int size;
    vector<vector<double>>* matriz;
    if (tablo == 1) {
        size = tamanho_real_col_auxiliar;
        matriz = &tableau1;
    } else {
        size = tamanho_real_col_principal;
        matriz = &tableau2;
    }

    // Transformar o pivô em 1 dividindo a linha inteira pelo valor do pivô
    double pivotValue = (*matriz)[pivotRow][pivotCol];
    if (abs(pivotValue) > EPSILON) {
        for (int j = 0; j < tamanho_real_col_auxiliar; j++) {
            (*matriz)[pivotRow][j] /= pivotValue;
        }
    }

    // Tornar os demais elementos da coluna do pivô em 0
    for (int i = 0; i < n + 1; i++) {
        if (i != pivotRow) {
            double factor = (*matriz)[i][pivotCol];
            for (int j = 0; j < tamanho_real_col_auxiliar; ++j) {
                (*matriz)[i][j] -= factor * (*matriz)[pivotRow][j];
                // Corrigir erros de precisão de ponto flutuante
                if (abs((*matriz)[i][j]) < EPSILON) {
                    (*matriz)[i][j] = 0.0;
                }
            }
        }
    }
}

//Nao esquecer de fzr o desempate
vector<int> SimplexAux(){
    // Construindo o vetor que representa a base atual(Inicialmente as var auxiliares)
    vector<int> base_hot(tamanho_real_col_auxiliar,0);
    
    //Forma canonica.
    for(int i = m+n-1, j = 0; i < base_hot.size()-2; i++, j++) {
        base_hot[i]=1;
        pivotTableau(j+1,i+1,1);
    }

    bool stop = false;
    while(!stop){
        //Escolhe  a primeira entrada negativa(var que entra na base)
        double min = -MIN;
        int pos=-1, var_entra=-1,var_sai=-1;
        for (int i = n; i < tamanho_real_col_auxiliar-1; i++){
            //Escolhe a que sai da base
            if(tableau1[0][i] < -EPSILON){
                var_entra = i;
                //Encontra a linha e a variavel q sai
                for(int j = 1; j <= n ; j ++){
                    if (abs(tableau1[j][i]) < EPSILON) continue;
                    double val = tableau1[j][tamanho_real_col_auxiliar-1] / tableau1[j][i];
                    if(tableau1[j][i] > EPSILON and  val < min) {
                        min = val, pos = j;
                        //Acha a variavel q sai
                        for (int i = n; i < tamanho_real_col_auxiliar; i++){
                            if(base_hot[i] == 1 and i != var_entra and tableau1[pos][i] == 1){
                                var_sai=i;
                            }
                        }
                    }else if (abs(val - min) < EPSILON){
                        int aux;
                        for (int i = n; i < tamanho_real_col_auxiliar; i++){
                            if(base_hot[i] == 1 and i != var_entra and tableau1[pos][i] == 1){
                                aux = i;
                            }
                        }
                        if (aux < var_sai){
                            var_sai = aux;
                            pos = j;
                        }
                    }
                }
                break;
            }
        }

        if(var_entra == -1) break;

        pivotTableau(pos,var_entra,1);
        base_hot[var_sai] = 0;
        base_hot[var_entra] = 1;

    }
    if (abs(tableau1[0][tamanho_real_col_auxiliar-1]) < EPSILON) existe_sol = true;
    if(!existe_sol) return base_hot;


    //Verifica se nenhuma das varivaeis auxiliares entrou na base
    for (int i = n+m, var = n; i < tamanho_real_col_auxiliar-1; i++){
        while(base_hot[var] == 1) var++;
        if(base_hot[i] == 1) base_inicial[i] = 0, base_inicial[var] = 1;
    }
    return base_hot;
}


// Realiza o Simplex principal e armaazena a solução na matriz tableau2
void SimplexPrincipal(){
    
    //Forma canonica.
    for(int i = 0, j = 0; i < base_inicial.size()-1; i++) {
        if(base_inicial[i] == 1){
            pivotTableau(j+1,i,2);
            j++;
        }
    }

    
    ilimitado = false;
    while(true){
        //Escolhe  a primeira entrada negativa(var que entra na base)
        double min = -MIN;
        int pos=-1, var_entra=-1, var_sai=-1;
        for (int i = n; i < tamanho_real_col_principal - 1; i++){
            if (tableau2[0][i] < -EPSILON){
                var_entra = i;
                // Encontra a linha
                for (int j = 1; j <= n; j++){
                    if (abs(tableau2[j][i]) < EPSILON) continue;
                    double val = tableau2[j][tamanho_real_col_principal - 1] / tableau2[j][i];
                    if (tableau2[j][i] > EPSILON and val < min){
                        min = val, pos = j;
                        for (int i = n; i < tamanho_real_col_principal; i++){
                            if (base_inicial[i] == 1 and i != var_entra and tableau2[pos][i] == 1){
                                var_sai = i;
                            }
                        }
                    }
                    else if (abs(val - min) < EPSILON){
                        int aux;
                        for (int i = n; i < tamanho_real_col_principal; i++){
                            if (base_inicial[i] == 1 and i != var_entra and tableau2[pos][i] == 1){
                                aux = i;
                            }
                        }
                        if (aux < var_sai){
                            var_sai = aux;
                            pos = j;
                        }
                    }

                    if(j==n and var_sai==-1) ilimitado = true, coluna_ilimitada = i;
                }
            }
        }

        if (ilimitado or var_entra == -1){
            break;
        }
        pivotTableau(pos, var_entra, 2);

        base_inicial[var_sai] = 0;
        base_inicial[var_entra] = 1;
        
    }
}

// Recupera a solução do problema que está na posição tableau2[0][tamanho_real_col_principal-1]
void recupera_solucao(){
    for (int i = n; i < n+m; i++){
        if(base_inicial[i] == 1){
            for (int j = 1; j < n+1; j++){
                if(tableau2[j][i] == 1){
                    cout << tableau2[j][tamanho_real_col_principal-1] << ' ';
                    break;
                }
                if (j == n) {
                    cout << 0 << ' ';
                }
            }
        }else {
            cout << 0 << ' ';
        }
        
    }
    cout << endl;
}

// Recupera o certificado otimo que está na linha 0, entre as colunas 0 e n da matriz tableau2
void recupera_certificado_otimo(){
    for (int i = 0; i < n; i++){
        cout << tableau2[0][i] << ' ';
    }
}


// Recupera o certificado inviavel que está na linha 0, entre as colunas 0 e n da matriz tableau1
void recupera_certificado_inviavel(){
    for (int i = 0; i < n; i++){
        cout << -tableau1[0][i] << ' ';
    }
}


// Recupera o certificado ilimitado que está no tableau2
void recupera_certificado_ilimitado(){
    vector<int> certificado(tamanho_real_col_auxiliar,0);
    for (int i = 1; i < n+1; i++){
        for(int j = n; j < n+m; j++){
            if(tableau2[i][j] == 1 and base_inicial[j] == 1){
                certificado[j] = -tableau2[i][coluna_ilimitada];
            }
        }
    }
    certificado[coluna_ilimitada] = 1;
    for (int i = n; i < n+m; i++){
        cout << certificado[i] << ' ';
    }
}

int main(){

    // Numero de restriçoes e Variaveis
    cin >> n >> m;
    Monta_tableau_principal(); 
    Monta_tableau_auxiliar();

    base_inicial = SimplexAux();

    if(existe_sol){
        SimplexPrincipal();

        if (ilimitado){
            cout << "ilimitada" << endl;
            recupera_solucao();
            recupera_certificado_ilimitado();
        }else {
            cout << "otima" << endl;
            cout << tableau2[0][tamanho_real_col_principal-1] << endl;
            recupera_solucao();
            recupera_certificado_otimo();
        }

    }else {
        cout << "inviavel" << endl;
        recupera_certificado_inviavel();
    }


    cout << endl;
    return 0;
}