#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

// Função para verificar se um número é primo
bool is_prime(int num) {
    if (num <= 1) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    for (int i = 3; i * i <= num; i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

// Função executada pela thread para imprimir números primos
void* print_primes(void* arg) {
    int max_number = *(int*)arg;

    printf("Números primos menores ou iguais a %d:\n", max_number);
    for (int i = 2; i <= max_number; i++) {
        if (is_prime(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");

    pthread_exit(NULL);
}

void* print_fibo(void* arg) {
    int max_number = *(int*)arg;

    printf("Números de Fibonacci menores ou iguais a %d:\n", max_number);
    int a = 0, b = 1, c = 0;
    while (c <= max_number) {
        printf("%d ", c);
        c = a + b;
        a = b;
        b = c;
    }
    printf("\n");

    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <número inteiro>\n", argv[0]);
        return 1;
    }

    int number = atoi(argv[1]);
    if (number < 2) {
        printf("Não há números primos menores ou iguais a %d.\n", number);
        return 0;
    }

    pthread_t* th = (pthread_t*) malloc(2 * sizeof(pthread_t));

    // Criando uma thread para calcular e imprimir os números primos
    if (pthread_create(&th[0], NULL, print_primes, &number) != 0) {
        perror("Erro ao criar a thread");
        return 1;
    }
    if (pthread_create(&th[1], NULL, print_fibo, &number) != 0) {
        perror("Erro ao criar a thread");
        return 1;
    }

    // Aguardando as threads terminarem
    for (int i = 0; i < 2; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Erro ao aguardar a thread");
            return 1;
        }
    }

    return 0;
}
