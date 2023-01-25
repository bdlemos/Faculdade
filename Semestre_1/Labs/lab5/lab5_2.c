#include <stdio.h>
#include <string.h>

typedef struct{
    char rua[50], estado[50];
    int num;
}endereco;

typedef struct{
    endereco adress;
    int age;
    float salario;
    char nome[50];
}pessoa;


int main()
{
    pessoa pessoas[4];
    char condition[10], nome[30];
    int cont = 0, i = 0;
    while(1){
        scanf("%s", condition);
        //INSERIR
        if (strcmp(condition,"inserir") == 0 && i < 4){
           scanf("%s%d%f%s%d%s", pessoas[i].nome, &pessoas[i].age, &pessoas[i].salario, pessoas[i].adress.rua, &pessoas[i].adress.num, pessoas[i].adress.estado);
           printf("Registro %s %d %.2f %s %d %s inserido\n", pessoas[i].nome, pessoas[i].age, pessoas[i].salario, pessoas[i].adress.rua, pessoas[i].adress.num, pessoas[i].adress.estado);
           i++;
        }else if (strcmp(condition,"inserir") == 0 && i > 3)
            printf("Espaco insuficiente\n");
        //MOSTRAR
        if (strcmp(condition,"mostrar") == 0){
            scanf("%s", nome);
            for(int j = 0 ; j < 4 ; ++j)
                if (strcmp(nome, pessoas[j].nome) == 0){
                    printf("Registro %s %d %.2f %s %d %s\n", pessoas[j].nome, pessoas[j].age, pessoas[j].salario, pessoas[j].adress.rua, pessoas[j].adress.num, pessoas[j].adress.estado);
                    cont++;
                    continue;
                }  
            if (cont == 0)
                printf("Registro ausente\n");
        }
        //ALTERAR
        if (strcmp(condition,"alterar") == 0){
            cont = 0;
            scanf("%s", nome);
            for(int j = 0 ; j < 4 ; ++j)
                if (strcmp(nome, pessoas[j].nome) == 0){
                    strcpy(pessoas[j].nome, nome);
                    scanf("%d%f%s%d%s", &pessoas[j].age, &pessoas[j].salario, pessoas[j].adress.rua, &pessoas[j].adress.num, pessoas[j].adress.estado);
                    printf("Registro %s %d %.2f %s %d %s alterado\n", pessoas[j].nome, pessoas[j].age, pessoas[j].salario, pessoas[j].adress.rua, pessoas[j].adress.num, pessoas[j].adress.estado);
                    cont++;
                    continue;
                }
            if (cont == 0)
                printf("Registro ausente para alteracao\n");
        }
    }
    return 0;
}