#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NUMBER 5

typedef struct{
    char name[100], sport[20];
    int age;
    float height;
} atleta;

int comparador(const void *a, const void *b) {
   return ( *(int*)a - *(int*)b );
}

int main(){
    atleta atletas[NUMBER];
    int idades[NUMBER];
    for (int i = 0 ;  i < NUMBER ; ++i){
        setbuf(stdin, NULL);
        fgets(atletas[i].name, 100, stdin);
        fgets(atletas[i].sport, 20, stdin);
        scanf("%d", &atletas[i].age);
        idades[i] = atletas[i].age;
    }
    qsort(idades, 5, sizeof(int), comparador);
    for (int i = NUMBER - 1 ; i >= 0 ; --i)
        printf("%d ", idades[i]);
    return 0;
}