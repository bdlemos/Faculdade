#include <string.h>
#include <stdio.h>
#define SIZE 8
typedef struct{
    char name[50], marca[50];
    float price;
} p;

int main(){
    p produtos[SIZE];
    float tmedia_price = 0, media_aux;
    char algo[200], algo2[200];
    int total_marca;
    //PREENCHE O VETOR DE STRUCT
    for(int i = 0 ; i < SIZE ; ++i)
        scanf("%s%s%f", produtos[i].name, produtos[i].marca, &produtos[i].price);
    //TOTAL POR MARCA
    for(int i = 0 ; i < SIZE ; ++i){
        total_marca = media_aux =  0;
        for (int j = 0 ; j < SIZE; ++j)
            if (strcmp(produtos[i].marca,produtos[j].marca) == 0)
                total_marca++;
        if(strstr(algo, produtos[i].marca) == 0)
            printf("%s %d\n", produtos[i].marca, total_marca);
        if (i == 0)
            strcpy(algo, produtos[i].marca);
        else
            strcat(algo, produtos[i].marca);
    }
    //MEDIA TOTAL
    for(int i = 0 ; i < SIZE ; ++i)
        tmedia_price += produtos[i].price/SIZE;
    printf("media total  %.2f\n", tmedia_price);
    //MEDIA POR MARCA
    for(int i = 0 ; i < SIZE ; ++i){
        total_marca = media_aux =  0;
        for (int j = 0 ; j < SIZE; ++j){
            if (strcmp(produtos[i].marca,produtos[j].marca) == 0){
                total_marca++;
                media_aux += produtos[j].price;
            }
        }
        if(strstr(algo2, produtos[i].marca) == 0)
            printf("media %s %.2f\n", produtos[i].marca, media_aux/total_marca);
        if (i == 0)
            strcpy(algo2, produtos[i].marca);
        else
            strcat(algo2, produtos[i].marca);
        }
    return 0;

}
