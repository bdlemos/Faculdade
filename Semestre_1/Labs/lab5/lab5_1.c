#include <stdio.h>
#include <string.h>

typedef struct{
    unsigned int age;
    float salario;
    char nome[50];
}pessoa;


int main()
{
    pessoa pessoas[4];
    char condition[10];
    char nome[30];
    int cont = 0, i = 0;
    while(scanf("%s", condition) != EOF){
        //scanf("%s", condition);
        //if (strcmp(condition, "inserir") != 0 && strcmp(condition, "mostrar") != 0)
            //break;
        if (strcmp(condition,"inserir") == 0 && i < 4){
           scanf("%s%d%f", pessoas[i].nome, &pessoas[i].age, &pessoas[i].salario);
           printf("Registro %s %d %.2f inserido\n", pessoas[i].nome, pessoas[i].age, pessoas[i].salario);
           i++;
        }else if (strcmp(condition,"inserir") == 0 && i > 3)
            printf("Espaco insuficiente\n");
        
        if (strcmp(condition,"mostrar") == 0){
            scanf("%s", nome);
            cont = 0;
            for(int j = 0 ; j < 4 ; ++j)
                if (strcmp(nome, pessoas[j].nome) == 0){
                    printf("Registro %s %d %.2f\n", pessoas[j].nome, pessoas[j].age, pessoas[j].salario);
                    cont++;
                    //break;
                }
            if (cont == 0)
                printf("Registro ausente\n");
        }
    }
    return 0;
}
