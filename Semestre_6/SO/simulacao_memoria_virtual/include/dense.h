#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#ifndef MY_DENSE_H

#define MY_DENSE_H

struct Frame {
    int addr_table;
    short int valid;
    short int dirty;
    int last_access;
    short int ref_bit;
} typedef Frame;

struct Page{
    int pos_in_mem;
    short int allocated;
} typedef Page;

struct Memory {
    Frame* frames;
    int size;
    const char* method;
    int skip;
    int first;
} typedef Memory;


Memory* create_memory(int size, const char* method, int skip) {
    Memory* memory = (Memory*) malloc(sizeof(Memory));
    memory->frames = (Frame*) malloc(size * sizeof(Frame));
    int count = 0;
    for (int i = 0; i < size; i++){
        memory->frames[i].addr_table = 0;    
        memory->frames[i].valid = -1;
        memory->frames[i].dirty = 0;
        memory->frames[i].last_access = 0;
        memory->frames[i].ref_bit = 0;
        count++;
    }
    memory->size = size;
    memory->skip = skip;
    memory->method = method;
    memory->first = 0;
    return memory;
}

void free_memory(Memory* memoria){
    free(memoria->frames);
    free(memoria);
};

Page* create_table(int skip){
    int table_size = pow(2, 32-skip);

    // Depende da abordagem. vamos considerar abordagem densa.dawds
    Page* table = (Page*) malloc(table_size * sizeof(Page));

    int count = 0;
    for (int i = 0; i < table_size; i++){
        table[i].pos_in_mem = -1; //CAUSAR ERRO DE SEGFAULT! cuidado.
        table[i].allocated = 0;
        count++;
    }
    return table;
}

int fifo_method(Memory* memoria){
    int position = memoria->first;
    memoria->first = (memoria->first + 1) % memoria->size;
    return position;
}

int lru_method(Memory* memoria){
    int position = 0;
    int last_access = memoria->frames[0].last_access;
    for (int i = 1; i < memoria->size; i++){
        if (memoria->frames[i].last_access < last_access){
            last_access = memoria->frames[i].last_access;
            position = i;
        }
    }
    return position;
}

int secondChance_method(Memory* memoria){
    int position = memoria->first;
    while (1){
        if (memoria->frames[position].ref_bit == 0){
            memoria->first = (memoria->first + 1) % memoria->size;
            return position;
        } else {
            memoria->frames[position].ref_bit = 0;
            memoria->first = (memoria->first + 1) % memoria->size;
            position = memoria->first;
        }
    }
}

int get_next_valid_position(Memory* memoria){
    int position = 0;

    if (strcmp(memoria->method, "random") == 0){
        position = rand() % (memoria->size);
    } else if (strcmp(memoria->method, "fifo") == 0){
        position = fifo_method(memoria);
    } else if (strcmp(memoria->method, "lru") == 0){
        position = lru_method(memoria);
    } else if (strcmp(memoria->method, "2a") == 0){
        position = secondChance_method(memoria);
    }
    return position;
}

int dense(int argc, char *argv[]) {
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

    Page* table = create_table(memoria->skip);
    

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

        if (table[true_addr].allocated){
            hits_count++;
            //Se a página já está na memória, atualiza o bit de referência para 1
            memoria->frames[table[true_addr].pos_in_mem].ref_bit = 1;
            int memory_addr = table[true_addr].pos_in_mem;
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
                    memoria->frames[position_to_allocate].addr_table = true_addr;
                    memoria->frames[position_to_allocate].dirty = (rw == 'W') ? 1 : 0;
                    table[true_addr].pos_in_mem = position_to_allocate;
                    table[true_addr].allocated = 1;
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
                memoria->frames[position_to_allocate].addr_table = true_addr;
                memoria->frames[position_to_allocate].dirty = (rw == 'W') ? 1 : 0;
                table[true_addr].pos_in_mem = position_to_allocate;
                table[true_addr].allocated = 1;
                table[old_addr].allocated = 0;
                table[old_addr].pos_in_mem = -1;
            }
        }
        memoria->frames[table[true_addr].pos_in_mem].last_access = num_of_access;
    }

    fclose(fileread);
    
    printf("Paginas lidas: %d\n", misses_count);
    printf("Paginas escritas: %d\n", writethrough);

    int bits_endereco = (32 - memoria->skip);
    int size_table = pow(2, bits_endereco);
    int gasto = (size_table * 4) /1024;

    // printf("Memória gasta: %d\n", gasto);

    free_memory(memoria);
    free(table);

    return 0;
}

#endif