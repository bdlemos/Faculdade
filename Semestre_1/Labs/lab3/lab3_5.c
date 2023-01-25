#include <stdio.h>

int main(){
	int r, c, menor, maior;
	scanf("%d%d", &r, &c);
	int M[r][c];
	for (int i = 0 ; i < r; i++){
		for (int j = 0 ; j < c; j++){
			scanf("%d", &M[i][j]);
			if (i == 0 && j == 0) maior = M[i][j];
			if (M[i][j] > maior)
				maior = M[i][j];
		}
	}
	printf("%d\n", maior);
	return 0;
}
