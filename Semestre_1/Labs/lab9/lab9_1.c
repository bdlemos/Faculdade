#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*enum meses_do_ano {
    Janeiro = 1, Fevereiro, Marco, Abril, Maio, Junho,
    Julho, Agosto, Setembro, Outubro, Novembro, Dezembro
}meses;*/
typedef struct{
    int dia, ano, mes;
}Data;

typedef struct{
    char nome[100], local[100];
    Data data;
}Evento;



void cadastrar_eventos(Evento *agenda, int n){
    for (int i = 0; i < n; i++)
        scanf("%s %s %d %d %d", agenda[i].nome, agenda[i].local, &agenda[i].data.dia, &agenda[i].data.mes, &agenda[i].data.ano);
    return;
}

void imprimir_eventos(Evento *agenda, Data d, int n){
    int cont = 0;
    for (int i = 0; i < n; i++){
        if (d.dia == agenda[i].data.dia && d.mes == agenda[i].data.mes && d.ano == agenda[i].data.ano){
            cont++;
            printf("%s %s\n", agenda[i].nome, agenda[i].local);
        }
    }
    if (cont == 0)
        printf("Nenhum evento encontrado!");
    return;
}

int main(){
    int n;
    Data date;
    Evento *vetor;
    scanf("%d", &n);
    vetor = (Evento*) malloc(n * sizeof(Evento));
    cadastrar_eventos(vetor, n);
    scanf("%d %d %d", &date.dia, &date.mes, &date.ano);
    imprimir_eventos(vetor, date, n);
    free(vetor);
    return 0;
}