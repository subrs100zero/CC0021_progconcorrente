#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
#define TAMANHO 100000000

double *gerar_vetor(int n);
int *gerar_vetor_inteiro(int n);
void mostrar_vetor_inteiro(int *v,int tamanho);
void mostrar_vetor(double *v,int tamanho);

int main() {
    time_t temp;
    double inicio,fim;
    srand(time(NULL));
    int *vetor = NULL;

    int x = 3;
    inicio = omp_get_wtime();
    int cont = 0;
    int temp = 0;

    vetor = gerar_vetor_inteiro(TAMANHO);

    #pragma omp parallel num_threads(4)
    {
        #pragma omp for
            for(long int i = 0; i < TAMANHO; i++){
                if(vetor[i] == x){
                    temp++;
                }
            }
            #pragma omp atomic
                cont += temp;
    }
    fim = omp_get_wtime();
    double tempo = fim - inicio;
    double media = cont/(float)TAMANHO;

    printf("OCORRENCIA: %d\n", cont);
    printf("MEDIA: %1f", media);
    printf("TEMPO: %f", tempo);
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
        int num = (rand() % MAX);
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