#include <stdio.h>

int main(){
	int a, c, menor, maior;
	scanf("%d", &a);
	int MA[a];
	for (int i  = 0 ; i < a ; ++i)
		scanf("%d", &MA[i]);
	scanf("%d", &c);
	int MC[c];
	for (int i  = 0 ; i < a ; ++i)
		scanf("%d", &MC[i]);
	menor = (a >= c) ? c : a;
	maior = (a <= c) ? c : a;
	for (int i = 0 ; i < maior; i++){
		for (int j = 0 ; j < menor; j++){
			if (MA[i] == MC[j])
				printf("%d\n", MA[i]);
		}
	}
	return 0;
}
