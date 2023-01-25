#include <stdio.h>
#include <stdlib.h>

int capturaSE(char **tab, int i, int j, char cor, int size){
    if ( i < 0 || i >= size || j < 0 || j >= (size/2) || tab[i][j] == cor || tab[i][j] == 'o')
        return 0;
    return 1 + capturaSE(tab, i + 1, j + 1, cor, size);
}
int capturaNE(char **tab, int i, int j, char cor, int size){
    if ( i < 0 || i >= size || j < 0 || j >= (size/2) || tab[i][j] == cor || tab[i][j] == 'o')
        return 0;
    return 1 + capturaNE(tab, i - 1, j + 1, cor, size);
}
int capturaNO(char **tab, int i, int j, char cor, int size){
    if ( i < 0 || i >= size || j < 0 || j >= (size/2) || tab[i][j] == cor || tab[i][j] == 'o')
        return 0;
    return 1 + capturaNO(tab, i - 1, j - 1, cor, size);
}
int capturaSO(char **tab, int i, int j, char cor, int size){
    if ( i < 0 || i >= size || j < 0 || j >= (size/2) || tab[i][j] == cor || tab[i][j] == 'o')
        return 0;
    return 1 + capturaSO(tab, i + 1, j - 1, cor, size);
}

int diagonal(char **tab, int i, int j, char cor, int size){
    int somaT = 0;
    int somaAux;
    if (cor == 'b' || cor == 'p'){
        //se
        somaT = capturaSE(tab, i + 1, j + 1, cor, size);
        //ne
        somaAux = capturaNE(tab, i - 1, j + 1, cor, size);
        somaT = (somaT > somaAux) ? somaT : somaAux;
        //no
        somaAux = capturaNO(tab, i - 1, j - 1, cor, size);
        somaT = (somaT > somaAux) ? somaT : somaAux;
        //so
        somaAux = capturaSO(tab, i + 1, j - 1, cor, size);
        somaT = (somaT > somaAux) ? somaT : somaAux;
    }
    return somaT;
}


void oportunidadeDeCaptura(char **tab, int **numOportunidade, int size){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size/2; j++){
                numOportunidade[i][j] = diagonal(tab, i, j, tab[i][j], size);     
        }
    }
}


int main(){
    char **tab;
    int **numOportunidade, size;
    scanf("%d", &size);
    
    tab = (char**) malloc(size * sizeof(char*));
    numOportunidade = (int**) malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++){
        tab[i] = (char*) malloc(size/2 * sizeof(char));
        numOportunidade[i] = (int*) malloc(size/2 * sizeof(int));
        for (int j = 0; j < size/2; j++){
            getchar();
            scanf("%c", &tab[i][j]);
        }
    }
    //printf("TESTE \n%c\n", tab[3][0]);
    oportunidadeDeCaptura(tab, numOportunidade,size);
    printf("\n");
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size/2; j++){
            if (numOportunidade[i][j] != 0){
                printf("%d %d %d\n", i, j * 2, numOportunidade[i][j]);
            }
        }
    }
    
    return 0;
}