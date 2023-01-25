#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[]){
    FILE *f;
    int soma = 0;
    f = fopen(argv[1], "r");
    if (f == NULL) return 1;
    while(!(feof(f))){
        int c = fgetc(f);
        if (c == 'a')
            soma++;
    }
    
    printf("%d", soma);
    fclose(f);
    return 0;
}