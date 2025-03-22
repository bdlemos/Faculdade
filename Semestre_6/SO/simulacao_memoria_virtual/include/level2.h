#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "dense.h"

#ifndef MY_H3_H

#define MY_H3_H

int hie3_l1_skip, hie3_l2_skip, hie3_l3_skip;
int hie3_l1_size, hie3_l2_size, hie3_l3_size;

struct l3Page{
    int pos_in_mem;
    short int allocated;
}typedef l3Page;

struct l2Page{
    l3Page* end_list;
    short int end_created;
} typedef l2Page;

struct l1Page{
    l2Page* middle_list;
    short int middle_created;
} typedef l1Page;

l1Page* H3_create_level1_table(Memory* memoria){
    //First, we need to define each size of the table.
    hie3_l1_skip = (32 - memoria->skip)/3;
    hie3_l2_skip = (32 - memoria->skip)/3;
    hie3_l3_skip = (32 - memoria->skip) - hie3_l1_skip - hie3_l2_skip;

    hie3_l1_size = pow(2, hie3_l1_skip);
    hie3_l2_size = pow(2, hie3_l2_skip);
    hie3_l3_size = pow(2, hie3_l3_skip);
    l1Page* level_table = (l1Page*) malloc(hie3_l1_size * sizeof(l1Page));
    int count = 0;
    for (int i = 0; i < hie3_l1_size; i++){
        level_table[i].middle_created = 0;
        level_table[i].middle_list = NULL;
        count++;
    }
    return level_table;
}

l2Page* H3_allocate_level2_table(l2Page* target_to_allocate){
    target_to_allocate = (l2Page*) malloc(hie3_l2_size*sizeof(l2Page));
    int count = 0;
    for (int i=0; i < hie3_l2_size; i++){
        target_to_allocate[i].end_created = 0;
        target_to_allocate[i].end_list = NULL;
        count++;
    }
    return target_to_allocate;
}

l3Page* H3_allocate_level3_table(l3Page* target_to_allocate){
    target_to_allocate = (l3Page*) malloc(hie3_l3_size*sizeof(l3Page));
    int count = 0;
    for (int i=0; i < hie3_l3_size; i++){
        target_to_allocate[i].allocated = 0;
        target_to_allocate[i].pos_in_mem = -1;
        count++;
    }
    return target_to_allocate;
}

int hie_two(int argc, char* argv[]){

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
    
    
    l1Page* level_table = H3_create_level1_table(memoria);
    
    unsigned addr;
    char rw;

    FILE* fileread = fopen(input_file, "r");

    int count_flag = 0;
    unsigned test;
    int hits_count, misses_count, writethrough, num_of_access;
    writethrough = hits_count = misses_count = num_of_access = 0;
    
    while(fscanf(fileread, "%x %c", &addr, &rw) != EOF){
        num_of_access++;
        int addr_level1, addr_level2, addr_level3, addr_skip;
        addr_skip = addr >> memoria->skip;
        addr_level1 = addr >> (memoria->skip + hie3_l2_skip + hie3_l3_skip);
        addr_level2 = (addr >> (memoria->skip + hie3_l3_skip)) & (hie3_l2_size-1);
        addr_level3 = (addr >> memoria->skip) & (hie3_l3_size -1);
        
        //verificamos se a segunda tabela foi criada.
        if (level_table[addr_level1].middle_created == 0){
            level_table[addr_level1].middle_list = H3_allocate_level2_table(level_table[addr_level1].middle_list);
            level_table[addr_level1].middle_created = 1;
        }

        //verificamos se a última tabela foi criada.
        if (level_table[addr_level1].middle_list[addr_level2].end_created == 0){
            level_table[addr_level1].middle_list[addr_level2].end_list = H3_allocate_level3_table(level_table[addr_level1].middle_list[addr_level2].end_list);
            level_table[addr_level1].middle_list[addr_level2].end_created = 1;
        }

        if (level_table[addr_level1].middle_list[addr_level2].end_list[addr_level3].allocated){
            hits_count++;
            //Se a página já está na memória, atualiza o bit de referência para 1
            memoria->frames[level_table[addr_level1].middle_list[addr_level2].end_list[addr_level3].pos_in_mem].ref_bit = 1;
            int memory_addr = level_table[addr_level1].middle_list[addr_level2].end_list[addr_level3].pos_in_mem;
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
                    level_table[addr_level1].middle_list[addr_level2].end_list[addr_level3].pos_in_mem = position_to_allocate;
                    level_table[addr_level1].middle_list[addr_level2].end_list[addr_level3].allocated = 1;
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
                level_table[addr_level1].middle_list[addr_level2].end_list[addr_level3].pos_in_mem = position_to_allocate;
                level_table[addr_level1].middle_list[addr_level2].end_list[addr_level3].allocated = 1;
                int lvl1_old, lvl2_old, lvl3_old;
                lvl1_old = old_addr >> (hie3_l2_skip + hie3_l3_skip);
                lvl2_old = (old_addr >> hie3_l3_skip) & (hie3_l2_size - 1);
                lvl3_old = old_addr & (hie3_l3_size-1);
                level_table[lvl1_old].middle_list[lvl2_old].end_list[lvl3_old].allocated = 0;
                level_table[lvl1_old].middle_list[lvl2_old].end_list[lvl3_old].pos_in_mem = -1;
            }
        }
        memoria->frames[level_table[addr_level1].middle_list[addr_level2].end_list[addr_level3].pos_in_mem].last_access = num_of_access;
    }

    fclose(fileread);
    
    //printf("Número de acessos: %d\n", num_of_access);
    printf("Paginas lidas: %d\n", misses_count);
    printf("Paginas escritas: %d\n", writethrough);

    int count_end = 0;
    for (int i = 0; i < hie3_l1_size; i++){
        if (level_table[i].middle_created == 1){
            
            for (int j = 0; j < hie3_l2_size; j++){
                if (level_table[i].middle_list[j].end_created == 1){
                    count_end++;
                }
            }
        }

    }

    int gasto = (count_end * hie3_l3_size) * 4; //Bytes
    gasto /= 1024;

    // printf("Memória gasta: %d\n", gasto);
    
    // dar free em tudo
    for (int i = 0; i < hie3_l1_size; i++){
        if (level_table[i].middle_created == 1){
            for (int j = 0; j < hie3_l2_size; j++){
                if (level_table[i].middle_list[j].end_created == 1){
                    free(level_table[i].middle_list[j].end_list);
                }
            }
            free(level_table[i].middle_list);
        }
    }
    free(level_table);
    free_memory(memoria);

    return 0;
}

#endif