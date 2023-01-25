#include <stdio.h>
#include <string.h>

int main(){
    int i, j, contador, contRep = 0;
    char nome[100];
    scanf("%s", nome);
    for ( i = 0 ; i  < strlen(nome); i++){
        for ( j = 0 ; j < strlen(nome); j++){
            if ( i != j && nome[i] == nome[j]){
                nome[i] = '0';
                contRep++;
            }
        }
    }
    contador = strlen(nome) - contRep;
    (contador % 2 == 0) ? printf("CHAT WITH HER!"): printf("IGNORE HIM!");
}