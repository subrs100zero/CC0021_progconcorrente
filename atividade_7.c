#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define N 1000000 // tamanho do conjunto de dados
#define THREADS 4 // número de threads a serem usadas

int main() {
    int i;
    float data[N];
    float mean = 0.0, std_dev = 0.0;
    
    // gerando dados aleatórios
    for (i = 0; i < N; i++) {
        data[i] = (float)rand() / RAND_MAX;
    }

    // calculando a média
    #pragma omp parallel for num_threads(THREADS) reduction(+:mean)
    for (i = 0; i < N; i++) {
        mean += data[i];
    }
    mean /= N;

    // calculando o desvio padrão
    #pragma omp parallel for num_threads(THREADS) reduction(+:std_dev)
    for (i = 0; i < N; i++) {
        std_dev += pow(data[i] - mean, 2);
    }
    std_dev = sqrt(std_dev / N);

    // exibindo resultados
    printf("Média: %f\nDesvio padrão: %f\n", mean, std_dev);

    return 0;
}
