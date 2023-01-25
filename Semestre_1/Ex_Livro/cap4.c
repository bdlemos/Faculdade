#include <stdio.h>
#include <math.h>

void ex1(){
    int x,y;
    printf("Digite um valor:");
    scanf("%d", &x);
    printf("Digite um valor:");
    scanf("%d", &y);
    (x > y) ? printf("x e maior\n") : printf("y e maior \n"); // if short
}

void ex2(){
    int x,y;
    printf("Digite um valor:");
    scanf("%d", &x);
    printf("Digite um valor:");
    scanf("%d", &y);
    (x > y) ? printf("x e maior\n"): (x < y) ? printf("y e maior \n"): printf("Os valores sao iguais\n") ;
    /*
    Ou assim tb funciona
    if (x > y){
        printf("X é maior\n");
    } 
    else if(x < y){
        printf("Y é maior \n");
    }
    else{
        printf("Os valores são iguais\n");
    }
    */
}

void ex3(){
    int x;
    printf("Digite um valor:");
    scanf("%d", &x);
    (x % 2 == 0) ? printf("E par\n") : printf ("Nao e par\n");
}

void ex4(){
    float salario, emprestimo_prestacao;
    printf("Digite o salario:");
    scanf("%f", &salario);
    printf("Digite a prestacao do emprestimo:");
    scanf("%f", &emprestimo_prestacao);
    (emprestimo_prestacao > salario*0.2) ? printf("Emprestimo nao concedido\n") : printf("Emprestimo concedido \n");
}

void ex5(){
    float x;
    printf("Digite um valor:");
    scanf("%f", &x);
    if (x >= 0){
        printf("O quadrado desse numero é: %.2f\n", x*x);
        printf("A raiz desse numero é: %.2f\n", sqrt(x));
    }
    else{
        printf("Valor invalido");
    }
}

void ex6(){
    float altura;
    char sexo;
    printf("Digite seu sexo:");
    scanf("%c", &sexo);
    printf("Digite a sua altura:");
    scanf("%f", &altura);
    switch(sexo){
        case 'm':
            printf("%.1f\n", (72.7*altura)-58);
            break;
        case 'f':
            printf("%.1f\n", (62.1*altura)-44.7);
            break;
        default:
            printf("Digite um sexo valido\n");
    } 
}

void ex7(){
    float valor;
    int estado;
    printf("Digite o valor do prdouto em reais:");
    scanf("%f", &valor);
    getchar();
    printf("Digite o estado destino: 1 - mg 2 - sp 3 - rj 4 - ms: ");
    scanf("%d", &estado);
    switch(estado){
        case 1:
            printf("O valor final para esse estado e %.2f\n", valor*1.07);
            break;
        case 2:
            printf("O valor final para esse estado e %.2f\n", valor*1.12);
            break;
        case 3:
            printf("O valor final para esse estado e %.2f\n", valor*1.15);
            break;
        case 4:
            printf("O valor final para esse estado e %.2f\n", valor*1.08);
            break;
        default:
            printf("Erro!\n");
    }
}

void ex8(){
    int idade;
    printf("Digite uma idade:");
    scanf("%i", &idade);
    if (idade >= 5 && idade <=7){
        printf("Infantil A\n");
    }
    else if (idade >= 8 && idade <=10){
        printf("Infantil B\n");
    }
    else if (idade >= 11 && idade <=13){
        printf("Juvenil A\n");
    }
    else if (idade >= 14 && idade <=17){
        printf("Juvenil B\n");
    }
    else if (idade > 18){
        printf("Senior\n");
    }
    else{
        printf("Bebe\n");
    }
}

void ex9(){
    float altura, peso;
    printf("Digite a sua altura em metros:");
    scanf("%f", &altura);
    printf("Digite seu peso:");
    scanf("%f", &peso);
    if (altura < 1.2 ){
        if (peso < 60){
            printf("A");
        }
        else if (peso >= 60 && peso <= 90){
            printf("D");
        }
        else{
            printf("G");
        }
    }
    else if (altura >= 1.2 && altura <= 1.7 ){
        if (peso < 60){
            printf("B");
        }
        else if (peso >= 60 && peso <= 90){
            printf("E");
        }
        else{
            printf("H");
        }
    }
    else{
        if (peso < 60){
            printf("C");
        }
        else if (peso >= 60 && peso <= 90){
            printf("F");
        }
        else{
            printf("I");
        }
    }
    printf("\n");
}

void ex10(){
}

void ex11(){
}

void ex12(){
}

void ex13(){
    float a, b, h;
    printf("Digite um cateto a:");
    scanf("%f", &a);
    printf("Digite um cateto b:");
    scanf("%f", &b);
    h = a*a + b*b;
    h = sqrt(h);
    printf("O valor da hipotenusa é %.2f\n", h);
}

void ex14(){
    char a;
    printf("Digite um char:");
    scanf("%c", &a);
    printf("%c\n", a+32);
}

void ex15(){
    float a, b, c, x1, x2, delta;
    scanf("%f%f%f", &a, &b, &c);
    delta = pow(b,2) + (-4*a*c);
    x1 = (-b + sqrt(delta))/(2*a);
    x2 = (-b - sqrt(delta))/(2*a);
    if (delta == 0){
        printf("Possui apenas uma raiz\nX = %.2f\n",x1);
    }else if (delta > 0){
        printf("Possui duas raizes\nX1 = %.2f e X2 = %.2f\n", x1, x2);
    }else{
        printf("Nao possui  raizes\n");
    }
}

int main(){
    ex15();
    return 0;
}