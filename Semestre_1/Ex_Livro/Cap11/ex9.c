#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* reversed_string(char *p){
    int size = strlen(p);
    char *string = (char*) malloc((size + 1) * sizeof(char));
    for (int i = 0, j = size - 1 ; p[i] != '\0' ; ++i, --j)
        string[i] = p[j];
    string[size] = '\0';
    return string;
}

int main(){
    int n;
    char p[100], *vet;
    printf("Digite a string: ");
    scanf("%s", p);
    vet = reversed_string(p);
    printf("%s \n", vet);
    free(vet);
    return 0;
}