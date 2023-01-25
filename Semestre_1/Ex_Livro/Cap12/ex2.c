#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *a1, *a2, *a3;
    a1 = fopen("teste1.txt", "r");
    a3 = fopen("teste3.txt", "w");
    while (!feof(a1))
        fputc(fgetc(a1), a3);
    fclose(a1);
    a2 = fopen("teste2.txt", "r");
    while (!feof(a2))
        fputc(fgetc(a2), a3);
    fclose(a2);
    fclose(a3);
    return 0;
}