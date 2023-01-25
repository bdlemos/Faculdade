#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    FILE *a1;
    char palavra[20], line[100];
    int cont = 0;
    scanf("%s", palavra);
    
    a1 = fopen("teste1.txt", "r");
    
    while (fgets(line, 100, a1) != NULL){
        char *tmp = line;
        while ((tmp = strstr(tmp, palavra)) != NULL){
            cont++;
            tmp++;
        }
    }
    printf("%d\n", cont);
    fclose(a1);
    return 0;
}