#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    FILE *a1, *a2;
    char str[20], str2[20];
    scanf("%s", str);
    scanf("%s", str2);
    
    a1 = fopen(str, "r");
    a2 = fopen(str2, "w");
    
    while (!feof(a1)){
        char c = fgetc(a1);
        if (c == 0) continue;
        if (c >= 65 && c <= 90) c += 32;
        fputc(c, a2);
    }
    fclose(a1);
    fclose(a2);
    return 0;
}