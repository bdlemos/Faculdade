#include <stdio.h>
#include <math.h>
#define PI 3.141592

void ex1(){
    int x;
    printf("Digite um valor:");
    scanf("%d", &x);
    printf("Antecessor: %d\nSucessor: %d\n", x - 1, x + 1);
}

void ex2(){
    float x;
    printf("Digite um valor:");
    scanf("%f", &x);
    printf("A quinta parte de x e %f\n", x / 5);
}

void ex3(){
    int x, y, z;
    printf("Digite 3 valores:");
    scanf("%d%d%d", &x, &y, &z);
    printf("A soma e %id\n", x + y + z);
}

void ex4(){
    float media, w, x, y, z;
    printf("Digite 4 valores:");
    scanf("%f%f%f%f", &w, &x, &y, &z);
    media = (w + x + y + z)/4;
    printf("A média e %.2f\n", media);
}

void ex5(){
    int x, y;
    printf("Digite sua idade:");
    scanf("%d", &x);
    printf("Digite o ano atual:");
    scanf("%d", &y);
    printf("Você nasceu em %i\n", y - x);
}

void ex6(){
    int kmh, ms;
    printf("Digite uma velocidade em km/h:");
    scanf("%d", &kmh);
    ms = kmh/3.6;
    printf("A velocidade em m/s é %d\n", ms);
}

void ex7(){
    float reais, dolar;
    printf("Digite uma quantidade em reais:");
    scanf("%f", &reais);
    printf("Digite a cotação atual:");
    scanf("%f", &dolar);
    printf("A o valor em dolares é $%.2f\n", reais/dolar);
}

void ex8(){
    float celsius, fahrenheit;
    printf("Digite uma tempratura em Celsius:");
    scanf("%f", &celsius);
    fahrenheit = celsius*9/5;
    printf("A temepratura em fahrenheit é %.2f F\n", fahrenheit);
}

void ex9(){
    float grau, radianos;
    printf("Digite um angulo em graus:");
    scanf("%f", &grau);
    radianos = grau*PI/180;
    printf("O angulo em radianos é %.2f rad\n", radianos);
}

void ex10(){
    float win1, win2, win3, prize = 780000;
    printf("O primeiro vencedor recebera %.2f\n", prize*42/100);
    printf("O segundo vencedor recebera %.2f\n", prize*32/100);
    printf("O terceiro vencedor recebera %.2f\n", prize*22/100);
}

void ex11(){
    float raio, area;
    printf("Digite um raio:");
    scanf("%f", &raio);
    area = (raio*raio)*PI;
    printf("A area do circulo e %.2f\n", area);
}

void ex12(){
    float raio, altura, area;
    printf("Digite um raio:");
    scanf("%f", &raio);
    printf("Digite uma altura:");
    scanf("%f", &altura);
    area = (raio*raio)*altura*PI;
    printf("A area do cilindro e %.2f\n", area);
}

void ex13(){
    float a, b, h;
    printf("Digite um cateto a:");
    scanf("%f", &a);
    printf("Digite um cateto b:");
    scanf("%f", &b);
    h = pow(a,2) + pow(b,2);
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
    int x, d1, d2, d3;
    printf("Digite um valor de 3 digitos:");
    scanf("%d", &x);
    d1 = x/100;
    x -= d1*100;
    d2 = (x/10);
    x -= d2*10;
    printf("%d%d%d\n", x, d2, d1);
}

void ex16(){
    int a;
    printf("Digite um valor:");
    scanf("%d", &a);
    printf("O dobro do valor é %d\nA metade do valor é %d\n", a<<1, a>>1);
}

void ex17(){
    int a;
    printf("Digite um valor:");
    scanf("%d", &a);
    printf("O complemento bit a bit desse valor é %d\n", ~a);
}

void ex18(){
    int a, b;
    printf("Digite um valor:");
    scanf("%d", &a);
    printf("Digite um valor:");
    scanf("%d", &b);
    printf("O deslocamento a esquerda do primeiro pelo segundo é %d\nO deslocamento a direita do primeiro pelo segundo é %d\n", a<<b, a>>b);
}

void ex19(){
    int a, b;
    printf("Digite um valor:");
    scanf("%d", &a);
    printf("Digite um valor:");
    scanf("%d", &b);
    printf("a XOR b = %d \na OR b = %d \na AND b = %d\n", a^b, a | b, a & b);
}
int main(){
    ex13();
    return 0;
}