#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "dense.h"

#ifndef MY_INVERSE_H

#define MY_INVERSE_H

int verify_if_alloc(Memory* memoria, int address){
    for (int i=0; i < memoria->size; i++){
        if (memoria->frames[i].addr_table == address){
            return i;
        }
    }
    
    return -1;
}

int inverse(int argc, char *argv[]) {

    unsigned int seed = time(0);
    srand(seed);

    char* used_algorithm = argv[1];
    char* input_file = argv[2];
    int page_size = atoi(argv[3]);
    int memory_size = atoi(argv[4]);
    
    printf("Executando o simulador...\n");
    printf("Arquivo de entrada: %s\n", input_file);
    printf("Tamanho da memoria: %d\n", memory_size);
    printf("Tamanho das paginas: %d\n", page_size);
    printf("Técnica de reposicao: %s\n", used_algorithm);

    memory_size *= 1024;
    page_size *= 1024;

    int tmp = page_size;
    unsigned s = 0;
    while (tmp > 1) {
        tmp = tmp>>1;
        s++;
    }

    int frame_amount = memory_size/page_size;
    Memory* memoria = create_memory(frame_amount, used_algorithm, s);

    unsigned addr;
    char rw;

    FILE* fileread = fopen(input_file, "r");

    int count_flag = 0;
    unsigned test;
    int hits_count, misses_count, writethrough, num_of_access;
    writethrough = hits_count = misses_count = num_of_access = 0;

    while(fscanf(fileread, "%x %c", &addr, &rw) != EOF){
        num_of_access++;
        int true_addr = addr >> memoria->skip;

        int get_addr = verify_if_alloc(memoria, true_addr);

        if (get_addr != -1){
            hits_count++;
            //Se a página já está na memória, atualiza o bit de referência para 1
            memoria->frames[get_addr].ref_bit = 1;
            int memory_addr = get_addr;
            if (rw == 'W'){
                memoria->frames[memory_addr].dirty = 1;
            }
        } else {
            misses_count++;
            int position_to_allocate = -1;
            //busca por uma posição vazia na memória e realiza o procedimento de miss, mas em caso de memória vazia.
            for (int i = 0; i < memoria->size; i++){
                if (memoria->frames[i].valid){
                    position_to_allocate = i;
                    get_addr = position_to_allocate;
                    memoria->frames[position_to_allocate].valid = 0;
                    memoria->frames[position_to_allocate].addr_table = true_addr;
                    memoria->frames[position_to_allocate].dirty = (rw == 'W') ? 1 : 0;
                    break;
                }
            }

            //caso contrário, todas as posições da memória estão cheias e temos que realizar o procedimento de tirar alguma página.
            if (position_to_allocate == -1){
                int position_to_allocate = get_next_valid_position(memoria);
                get_addr = position_to_allocate;
                // Se a página que será retirada da memória estiver suja, incrementa o contador de escritas.
                if (memoria->frames[position_to_allocate].dirty){
                    writethrough++;
                }
                memoria->frames[position_to_allocate].addr_table = true_addr;
                memoria->frames[position_to_allocate].dirty = (rw == 'W') ? 1 : 0;
            }
        }
        memoria->frames[get_addr].last_access = num_of_access;
    }

    fclose(fileread);
    
    printf("Paginas lidas: %d\n", misses_count);
    printf("Paginas escritas: %d\n", writethrough);

    int gasto = (memoria->size * 8)/1024;
    // printf("Memória gasta: %d\n", gasto);
    free_memory(memoria);
    return 0;
}

#endif