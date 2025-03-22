#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "dense.h"

#ifndef MY_LVL1_H

#define MY_LVL1_H

int level1_skip, level2_skip, level1_size, level2_size;

struct level2Page{
    int pos_in_mem;
    short int allocated;
} typedef level2Page;

struct level1Page{
    level2Page* second_list;
    short int created;
} typedef level1Page;

level1Page* create_level1_table(Memory* memoria){
    //First, we need to define each size of the table.
    level1_skip = (32 - memoria->skip)/2;
    level2_skip = (32 - memoria->skip) - level1_skip;
    level1_size = pow(2, level1_skip);
    level2_size = pow(2, level2_skip);
    //printf("L1 size and skip: %d %d\nL2 Size: %d %d\n", level1_size, level1_skip, level2_size, level2_skip); //debug
    level1Page* level_table = (level1Page*) malloc(level1_size * sizeof(level1Page));
    int count = 0;
    for (int i = 0; i < level1_size; i++){
        level_table[i].created = 0;
        level_table[i].second_list = NULL;
        count++;
    }
    //printf("debug create_table %d\n", count);
    return level_table;
}




level2Page* allocate_level2_table(level2Page* target_to_allocate){
    target_to_allocate = (level2Page*) malloc(level2_size*sizeof(level2Page));
    int count = 0;
    for (int i=0; i < level2_size; i++){
        target_to_allocate[i].allocated = 0;
        target_to_allocate[i].pos_in_mem = -1;
        count++;
    }
    //printf("debug allocate_level_2: %d\n", count);
    return target_to_allocate;
}


int hie_one(int argc, char* argv[]){

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

    level1Page* level_table = create_level1_table(memoria);
    
    unsigned addr;
    char rw;

    FILE* fileread = fopen(input_file, "r");

    int count_flag = 0;
    unsigned test;
    int hits_count, misses_count, writethrough, num_of_access;
    writethrough = hits_count = misses_count = num_of_access = 0;
    
    while(fscanf(fileread, "%x %c", &addr, &rw) != EOF){
        num_of_access++;
        int addr_level1, addr_level2, addr_skip;
        addr_skip = addr >> memoria->skip;
        addr_level1 = addr >> (memoria->skip + level2_skip);
        addr_level2 = (addr >> memoria->skip) & (level2_size-1);
        if (addr_level1 >= 1024){
            printf("explodiu");
        }
        if (addr_level2 >= 1024){
            printf("explodiu");
        }
        
        //verificamos se a tabela foi criada.
        if (level_table[addr_level1].created == 0){
            level_table[addr_level1].second_list = allocate_level2_table(level_table[addr_level1].second_list);
            level_table[addr_level1].created = 1;
        }
        
        if (level_table[addr_level1].second_list[addr_level2].allocated){
            hits_count++;
            //Se a página já está na memória, atualiza o bit de referência para 1
            memoria->frames[level_table[addr_level1].second_list[addr_level2].pos_in_mem].ref_bit = 1;
            int memory_addr = level_table[addr_level1].second_list[addr_level2].pos_in_mem;
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
                    memoria->frames[position_to_allocate].valid = 0;
                    memoria->frames[position_to_allocate].addr_table = addr_skip;
                    memoria->frames[position_to_allocate].dirty = (rw == 'W') ? 1 : 0;
                    level_table[addr_level1].second_list[addr_level2].pos_in_mem = position_to_allocate;
                    level_table[addr_level1].second_list[addr_level2].allocated = 1;
                    break;
                }
            }

            //caso contrário, todas as posições da memória estão cheias e temos que realizar o procedimento de tirar alguma página.
            if (position_to_allocate == -1){
                int position_to_allocate = get_next_valid_position(memoria);
                // Se a página que será retirada da memória estiver suja, incrementa o contador de escritas.
                if (memoria->frames[position_to_allocate].dirty){
                    writethrough++;
                }

                int old_addr = memoria->frames[position_to_allocate].addr_table;
                memoria->frames[position_to_allocate].addr_table = addr_skip;
                memoria->frames[position_to_allocate].dirty = (rw == 'W') ? 1 : 0;
                level_table[addr_level1].second_list[addr_level2].pos_in_mem = position_to_allocate;
                level_table[addr_level1].second_list[addr_level2].allocated = 1;
                int lvl1_old, lvl2_old;
                lvl1_old = old_addr >> level2_skip;
                lvl2_old = old_addr & (level2_size - 1);
                level_table[lvl1_old].second_list[lvl2_old].allocated = 0;
                level_table[lvl1_old].second_list[lvl2_old].pos_in_mem = -1;
            }
        }
        memoria->frames[level_table[addr_level1].second_list[addr_level2].pos_in_mem].last_access = num_of_access;
    }

    fclose(fileread);
    printf("Paginas lidas: %d\n", misses_count);
    printf("Paginas escritas: %d\n", writethrough);

    int count=0;
    for (int i = 0; i < level1_size; i++){
        if (level_table[i].created == 1){
            count++;
        }
    }

    int qt_gasta = (count * level2_size) * 4; //Bytes.
    qt_gasta /= 1024; //Kbytes.
    // printf("Memória gasta: %d\n", qt_gasta);

    // dar free em tudo
    for (int i = 0; i < level1_size; i++){
        if (level_table[i].created == 1){
            free(level_table[i].second_list);
        }
    }
    free(level_table);
    free_memory(memoria);

    return 0;
}

#endif
