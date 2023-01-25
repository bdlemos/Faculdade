#include "jogo_da_vida.h"

JogoDaVida::JogoDaVida(int l, int c){
    vivas_.resize(l);
    for (int i = 0; i < l; i++)
        for (int j = 0; j < c; j++)
            vivas_[i].push_back(false);
}

bool JogoDaVida::viva(int i, int j){
    if((i < 0 or i >= vivas_.size()) or (j < 0 or j >= vivas_[i].size()))
        throw ExcecaoCelulaInvalida{i,j};
    return vivas_[i][j];
}

void JogoDaVida::Matar(int i, int j){
    if((i < 0 or i >= vivas_.size()) or (j < 0 or j >= vivas_[0].size()))
        throw ExcecaoCelulaInvalida{i,j};
    vivas_[i][j] = false;
}

void JogoDaVida::Reviver(int i, int j){
    if((i < 0 or i >= vivas_.size()) or (j < 0 or j >= vivas_[i].size()))
        throw ExcecaoCelulaInvalida{i,j};
    vivas_[i][j] = true;
}

void JogoDaVida::ExecutarProximaIteracao(){
    int l = linhas();
    int c = colunas();
    std::vector<std::vector<int>> Viz_vivos(l, std::vector<int>(c));

    for (int i = 0; i < l; i++)
        for (int j = 0; j < c; j++)
            Viz_vivos[i][j] = NumeroDeVizinhasVivas(i,j);
        
    for (int i = 0; i < l; i++){
        for (int j = 0; j < c; j++){
            if((Viz_vivos[i][j] > 3 || Viz_vivos[i][j] <= 1) && viva(i,j))
                Matar(i,j);
            else if(Viz_vivos[i][j] == 3 && !viva(i,j))
                Reviver(i,j);
            
        }
    }
}

int JogoDaVida::NumeroDeVizinhasVivas(int x, int y){
    int count = 0;
    int c_a, c_p, l_a, l_p;

    l_a = (x == 0) ? linhas() - 1 : x - 1;
    c_a = (y == 0) ? colunas() - 1 : y - 1;
    l_p = (x == linhas() - 1) ? 0 : x + 1;
    c_p = (y == colunas() - 1) ? 0 : y + 1;

    if(vivas_[l_a][c_a]) count++;
    if(vivas_[l_a][y]) count++;
    if(vivas_[l_a][c_p]) count++;
    if(vivas_[l_p][c_a]) count++;
    if(vivas_[l_p][y]) count++;
    if(vivas_[l_p][c_p]) count++;
    if(vivas_[x][c_a]) count++;
    if(vivas_[x][c_p]) count++;
    
    return count;
}