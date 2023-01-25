#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    FILE *a1;
    char str[20], oi[1000];
    int n;
    scanf("%s", str);
    
    a1 = fopen(str, "r");
    //fread(oi, sizeof(char), 1000, a1); // le ate o final
    fgets(oi, 1000, a1); // le ate o \n
    //fscanf(a1 ,"%s", oi); // le ate o espaço
    printf("%s", oi);
    return 0;
}