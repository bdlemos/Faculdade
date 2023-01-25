#include <stdio.h>
#include <stdlib.h>

void preencher(int* ponteiro, int size){
    for (int i = 0; i < size; i++){
        ponteiro[i]=i+1;
        printf("%d ", ponteiro[i]);
    }
}

int main(){
    int* ptr;
    int size;
    scanf("%d", &size);
    ptr = (int *) malloc(size*sizeof(int));
    preencher(ptr, size);
    free(ptr);
    return 0;
}