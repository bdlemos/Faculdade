#include <stdio.h>

void fibonacci(int n){
	int vetor[800];
	vetor[0] = vetor[1] = 1;
	
	for (int i = 2 ; i < n; ++i)
		vetor[i] = vetor[i-1] + vetor[i-2];
	printf("%d\n", vetor[n-1]);
}

int main(){
	int n = 1;
	while (1){
		scanf("%d", &n);
		if (n > 800 || n < 0)
			break;
		fibonacci(n);
	}
	return 0;
}