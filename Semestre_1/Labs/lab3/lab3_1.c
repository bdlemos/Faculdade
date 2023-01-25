#include <stdio.h>

void primos(int a, int b){
	int contador;
	(a == 1) ? a++: a; 
	while (a <= b){
		contador = 0;
		for(int i = 2 ; i*i <= a ;++i)
			if (a % i == 0){
				contador++;
				break;
			}
		if (contador == 0)
			printf("%d\n", a);
		a++;
	}
}

int main(){
	int a, b;
	scanf("%d%d", &a, &b);
	primos(a, b);
	return 0;
}
