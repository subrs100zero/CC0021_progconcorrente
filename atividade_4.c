#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define TAMANHO 100000000
#define max 100

int main() {
    int i;
    long int soma = 0;

    printf("execucao sequencial: \n");
    double inicio = omp_get_wtime();
    double fim = omp_get_wtime();
    for(i = 1; i<=max;i++){
        if(max%i == 0){

        }
    }
    printf("Soma dos divisores: %d\n, soma");
    fim = omp_get_wtime();
    double tempo2 = fim - inicio;
    printf("tempo execução: %.5f\n", tempo2);
    soma = 0;
    printf("\nParalela estatica com reduction");
    inicio = omp_get_wtime();
    #pragma omp parallel
    {
        int aux = 0;
        #pragma omp for
            for(i = 1; i<=max;i++){
                if(max%i == 0){
                    aux = aux + 1;
                }
            }
            #pragma 
    }
}


double *gerar_vetor(int n) {
    double *vetor;
    int i;
    vetor = (double *)malloc(sizeof(double) * n);
    for (i=0;i<n;i++) {
        double num = (rand() / (float)RAND_MAX);
        vetor[i] = num;
    }
    return vetor;
}

int *gerar_vetor_inteiro(int n) {
    int *vetor;
    int i;
    vetor = (int *)malloc(sizeof(int) * n);
    for (i=0;i<n;i++) {
        int num = (rand() % max);
        vetor[i] = num;
    }
    return vetor;
}

void mostrar_vetor(double *v,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%.5f]",v[i]);
    }
    printf("\n");
}

void mostrar_vetor_inteiro(int *v,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%d]",v[i]);
    }
    printf("\n");
    
}