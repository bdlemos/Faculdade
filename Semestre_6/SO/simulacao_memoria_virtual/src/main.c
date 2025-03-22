#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "dense.h"
#include "level1.h"
#include "level2.h"
#include "inverse.h"

void execute_dense(int argc, char* argv[]){
        printf("Execução Densa: \n");
        float tinicio, tfim;
        tinicio = clock();
        dense(argc, argv);
        tfim = clock();
        // printf("Tempo de execucao: %f\n", (tfim - tinicio)/CLOCKS_PER_SEC);
        printf("\n");
}

void execute_level2(int argc, char* argv[]){
        printf("Execução Hierarquica de 2 nível: \n");
        float tinicio, tfim;
        tinicio = clock();
        hie_one(argc, argv);
        tfim = clock();
        // printf("Tempo de execucao: %f\n", (tfim - tinicio)/CLOCKS_PER_SEC);
        printf("\n");
}

void execute_level3(int argc, char* argv[]){
        printf("Execução Hierarquica de 3 níveis: \n");
        float tinicio, tfim;
        tinicio = clock();
        hie_two(argc, argv);
        tfim = clock();
        // printf("Tempo de execucao: %f\n", (tfim - tinicio)/CLOCKS_PER_SEC);
        printf("\n");
}

void execute_inverse(int argc, char* argv[]){
        printf("Execução Invertida: \n");
        float tinicio, tfim;
        tinicio = clock();
        inverse(argc, argv);
        tfim = clock();
        // printf("Tempo de execucao: %f\n", (tfim - tinicio)/CLOCKS_PER_SEC);
        printf("\n");
}

int main(int argc, char* argv[]){
    if (argc < 5 || argc > 6) {
        printf("Erro: Numero de argumentos invalidos\n");
        return 1;
    }

    if (argc == 5){
        execute_dense(argc, argv);
        execute_level2(argc, argv);
        execute_level3(argc, argv);
        execute_inverse(argc, argv);
    }else{
        if (strcmp(argv[5], "dense") == 0){
            execute_dense(argc, argv);
        }else if (strcmp(argv[5], "level2") == 0){
            execute_level2(argc, argv);
        }else if (strcmp(argv[5], "level3") == 0){
            execute_level3(argc, argv);
        }else if (strcmp(argv[5], "inverse") == 0){
            execute_inverse(argc, argv);
        }else{
            printf("Error: Invalid algorithm\n");
            return 1;
        }
        
    }
    

    return 0;
}

