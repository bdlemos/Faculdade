#include <stdio.h>
#include <string.h>
#define NUMBER 5

typedef struct{
    char name[100], sport[20];
    int age;
    float height;
} atleta;

int main(){
    atleta atletas[NUMBER], older, heighter;
    older.age = 0;
    heighter.height = 0;
    for (int i = 0 ;  i < NUMBER ; ++i){
        setbuf(stdin, NULL);
        fgets(atletas[i].name, 100, stdin);
        fgets(atletas[i].sport, 20, stdin);
        scanf("%d%f", &atletas[i].age, &atletas[i].height);
        if (atletas[i].age > older.age)
            older = atletas[i];
        if (atletas[i].height > heighter.height)
            heighter = atletas[i];
    }
    printf("Mais velho: %s \nMais alto: %s\n", older.name, heighter.name);
    return 0;
}