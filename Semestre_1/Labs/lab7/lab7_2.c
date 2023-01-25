#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[]){
    FILE *f;
    int soma = 0;
    char s[300000];
    scanf("%s", s);
    f = fopen(s, "r");
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