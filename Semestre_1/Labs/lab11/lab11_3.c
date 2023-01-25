#include <stdio.h>
#include <string.h>

int carater(char *c, char letra){
    int soma = 0;
    if(*c == '\0')
        return 0;
    if(*c == letra)
        soma = 1 + carater(c + 1, letra);
    else
        soma = 0 + carater(c + 1, letra);
    return soma;
}

int main(){
    char str[100], letra;
    int soma;
    scanf("%s", str);
    getchar();
    scanf("%c", &letra);
    soma = carater(str, letra);
    printf("%d", soma);
    return 0;
}