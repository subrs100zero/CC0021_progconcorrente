#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int *gerar_vetor_binario(int n) {
    int *vetor;
    int i;
    vetor = (int *)malloc(sizeof(int) * n);
    for (i = 0; i < n; i++) {
        int num = rand() % 2;
        vetor[i] = num;
    }
    return vetor;
}

int main() {
    int p = 4; // Número de processadores
    int n = 100; // Tamanho do vetor binário
    int *vetor = gerar_vetor_binario(n);

    int contador[2] = {0}; // Contador de 0s e 1s
    int i;

    // Contagem paralela usando OpenMP
    #pragma omp parallel for num_threads(p) reduction(+:contador[:2])
    for (i = 0; i < n; i++) {
        contador[vetor[i]]++;
    }

    // Verifica a paridade
    int paridade = contador[1] % 2;

    // Adiciona um 0 ou um 1 para tornar o número de 1s par
    if (paridade == 1) {
        vetor[n - 1] = 0;
    }

    // Imprime o vetor resultante
    printf("Vetor binário resultante:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    free(vetor);

    return 0;
}
