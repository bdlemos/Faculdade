/*Crie uma enumeração representando os dias da semana. Agora, escreva um programa que leia um valor inteiro do teclado e exiba o dia da semana correspondente.*/
 #include <stdio.h>

 enum dias {Domingo = 1 , Segunda, Terca, Quarta, Quinta, Sexta, Sabado};

 int main(){
    int day;
    enum dias oi;
    scanf("%d", &day);
    switch (day){
        case Domingo:
            printf("Domingo\n");
            break;
        case Segunda:
            printf("Segunda\n");
            break;
        case Terca:
            printf("Terca\n");
            break;
        case Quarta:
            printf("Quarta\n");
            break;
        case Quinta:
            printf("Quinta\n");
            break;
        case Sexta:
            printf("Sexta\n");
            break;
        case Sabado:
            printf("Sabado\n");
            break;
        default:
            printf("Invalido\n");
    }
    return 0;
 }