#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char name[50];
    int age;
    char tel[20];
} agenda;

int main(int argc, char *argv[]){
    FILE *f;
    char s[100], operation[20];
    agenda agenda[100];
    scanf("%s", s);
    f = fopen(s, "rb");
    if (f == NULL) return 1;
    for (int i = 0; i < 100; i++){
        agenda[i].age = 0;
    }
    fread(agenda, sizeof(agenda), 100, f);
    fclose(f);
    while(scanf("%s", operation) != EOF){
        
        if (strcmp(operation,"Inserir") == 0){
            for (int i = 0; i < 100; i++){
                if(agenda[i].age == 0){
                    char name[50];
                    int age;
                    char tel[20];
                    scanf("%s%d%s", name, &age, tel);
                    strcpy(agenda[i].name, name);
                    agenda[i].age = age;
                    strcpy(agenda[i].tel, tel);
                    printf("Registro %s %d %s inserido\n", name, age, tel);
                    break;
                }else if (i == 99)
                    printf("Espaco insuficiente\n");
            }


        }else if (strcmp(operation,"Alterar") == 0){
            char name[50];
            int age;
            char tel[20];
            scanf("%s%d%s", name, &age, tel);
            for (int i = 0; i < 100; i++){
                if (strcmp(agenda[i].name, name) == 0){
                    strcpy(agenda[i].name, name);
                    agenda[i].age = age;
                    strcpy(agenda[i].tel, tel);
                    printf("Registro %s %d %s alterado\n", name, age, tel);
                    break;
                }
                if (i == 99) 
                    printf("Registro %s invalido\n", name);
            }
            
        }else if (strcmp(operation,"Excluir") == 0){
            char name[50];
            scanf("%s", name);
            for (int i = 0; i < 100; i++){
                if (strcmp(agenda[i].name, name) == 0){
                    printf("Registro %s %d %s excluido\n", agenda[i].name, agenda[i].age, agenda[i].tel);
                    strcpy(agenda[i].name, "");
                    agenda[i].age = 0;
                    strcpy(agenda[i].tel, "");
                    break;
                }
                if (i == 99) 
                    printf("Registro %s invalido\n", name);
            }
        }else if (strcmp(operation,"Exibir") == 0){
            char name[50];
            scanf("%s", name);
            for (int i = 0; i < 100; i++){
                if (strcmp(agenda[i].name, name) == 0){
                    printf("Registro %s %d %s exibido\n", agenda[i].name, agenda[i].age, agenda[i].tel);
                    break;
                }
                if (i == 99) 
                    printf("Registro %s invalido\n", name);
            }
        }
        
    }
    for (int i = 0; i < 100; i++){
        fputs(agenda[i].name, f);
        fputs(" ", f);
        fprintf(f, "%d", agenda[i].age);
        fputs(" ", f);
        fputs(agenda[i].name, f);
        fputs("\n", f);

    }
    fclose(f);
    return 0;
}