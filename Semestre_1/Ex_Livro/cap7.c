#include <stdio.h>
#include <string.h>

void ex_1(){
    char texto[10];
    setbuf(stdin, NULL);
    fgets(texto, 10, stdin); // isso aqui le ate o enter
    fputs(texto, stdout);
}

void ex_2(){
    char texto[10];
    setbuf(stdin, NULL);
    fgets(texto, 5, stdin); 
    fputs(texto, stdout);
}

void ex_3(){
    char texto[100];
    setbuf(stdin, NULL);
    fgets(texto, 100, stdin);
    for ( int i = 0 ;; ++i){
        if (texto[i] == '\0'){
            printf("%d\n", i-1);
            break;
        }
    }
    printf("%ld", strlen(texto));
}

void ex_4(){
    // print ao contrario
    char texto[100];
    setbuf(stdin, NULL);
    fgets(texto, 100, stdin);
    for ( int i = strlen(texto)-2 ; i >= 0 ; --i){ // coloquei o -2 pq o ultimo caracter é \0 e o penultimo é o \n
        printf("%c", texto[i]);
    }
    printf("\n");
}

void ex_5(){
    //inverte string
    char principal[100], auxiliar [100];
    setbuf(stdin, NULL);
    fgets(principal, 100, stdin);
    strcpy(auxiliar, principal);
    for (int j = strlen(principal) - 2, i = 0 ; i < strlen(principal) - 1; ++i, --j){ // -2 pq os dois ultimos sao \n e \0 || -1 pq o strlen conta com o \n
        principal[i] = auxiliar[j];
    }
    fputs(principal, stdout);
}

void ex_6(){
    char texto[100],  caracter;
    int contador = 0;
    setbuf(stdin, NULL);
    fgets(texto, 100, stdin);
    scanf("%c", &caracter);
    for (int i = 0 ; i < strlen(texto) ; ++i ){
        if(texto[i] == 'a' || texto[i] == 'e' || texto[i] == 'i' || texto[i] == 'o' || texto[i] == 'u'){
            contador++;
            texto[i] = caracter;
        }
    }
    fputs(texto, stdout);
    printf("O numero de vogais era %d\n", contador);
}

void ex_7(){
    char principal[100], auxiliar [100];
    setbuf(stdin, NULL);
    fgets(principal, 100, stdin);
    strcpy(auxiliar, principal);
    for (int j = strlen(principal)-2, i = 0 ; i < strlen(principal)-1; ++i, --j){ // -2 pq os dois ultimos sao \n e \0 || -1 pq o strlen conta com o \n
        principal[i] = auxiliar[j];
    }
    (strcmp(principal, auxiliar)) ? printf("Nao eh palindromo\n"): printf("Eh palindromo\n");
}

void ex_8(){
    int condicao = 0;
    char x[100], y[100];
    fgets(x, 100, stdin);
    fgets(y, 100, stdin);
    for (int i = 0 ; i < strlen(x) ; ++i){
        for (int j = 0 ; j < strlen(y) ; ++j){
            if (y[j] == x[i]){
                condicao = 1;
                break;
            }else{
                condicao = 0;
            }
        }
    }
    if (condicao == 0){
        printf("A segunda nao esta na primeira\n");
    }else{
        printf("A segunda esta na primeira\n");
    }
    
}

void ex_10(){
    char x[100];
    scanf("%s", x);
    for (int i = 0 ;  i < strlen(x) ; ++i){
        x[i] -= 32;
    }
    fputs(x, stdout);
    printf("\n");
}

void ex_11(){
    char x[100];
    scanf("%s", x);
    for (int i = 0 ;  i < strlen(x) ; ++i){
        x[i] += 32;
    }
    fputs(x, stdout);
    printf("\n");
}

void ex_12(){
    float valor;
    char x[100];
    scanf("%s %f", x, &valor);
    printf("%s | %.2f | %.2f | %.2f ", x, valor, valor*0.1, valor*0.9);
    printf("\n");
}

void ex_13(){
    char x[100];
    unsigned int i, j;
    fgets(x, 100, stdin);
    scanf("%i%i", &i, &j);
    for (; i <= j ; ++i){
        printf("%c", x[i]);
    }
}

void ex_14(){
    char x[100], y[100];
    fgets(x, 100, stdin);
    for (int i = 0; i < strlen(x); ++i){
        if (x[i] == 'z' || x[i] == 'x' || x[i] == 'y'){
            y[i] = x[i] - 23;
        }else if (x[i] != ' '){
            y[i] = x[i] + 3;
        }else{
            y[i] = x[i];
        }
    }
    printf("%s\n", y);
}

void ex_15(){
    char x[100], y[100], matriz[26][1];
    fgets(x, 100, stdin);
    fgets(y, 100, stdin);
    if (strcmp(x,y) == 0){
        printf("Iguais");
    }else if(strcmp(x,y) == 1){
        printf("%s%s", x, y);
    }else{
        printf("%s%s", y, x);
    }
}

int main(){
    ex_15();
    return 0;
}