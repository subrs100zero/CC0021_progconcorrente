#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

double calcularMedia(double *valores, int tamanho) {
    double soma = 0.0;
    int i;
    for (i = 0; i < tamanho; i++) {
        soma += valores[i];
    }
    return soma / tamanho;
}

double calcularDesvioPadrao(double *valores, int tamanho, double media) {
    double soma = 0.0;
    int i;
    for (i = 0; i < tamanho; i++) {
        soma += pow(valores[i] - media, 2);
    }
    return sqrt(soma / tamanho);
}

int main(int argc, char** argv) {
    int meuRank, numProcessos, elementosPorProcesso, resto;
    double *valores = NULL;
    double *meusValores = NULL;
    double media, desvioPadrao;
    int i;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meuRank);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcessos);

    if (meuRank == 0) {
        int tamanho = 0;

        printf("Informe o número total de elementos: ");
        scanf("%d", &tamanho);

        elementosPorProcesso = tamanho / numProcessos;
        resto = tamanho % numProcessos;

        valores = (double*)malloc(tamanho * sizeof(double));
        printf("Informe os valores:\n");
        for (i = 0; i < tamanho; i++) {
            scanf("%lf", &valores[i]);
        }
    }

    MPI_Bcast(&elementosPorProcesso, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&resto, 1, MPI_INT, 0, MPI_COMM_WORLD);

    meusValores = (double*)malloc(elementosPorProcesso * sizeof(double));

    MPI_Scatter(valores, elementosPorProcesso, MPI_DOUBLE, meusValores, elementosPorProcesso, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double minhaMedia = calcularMedia(meusValores, elementosPorProcesso);
    double minhaSoma = 0.0;

    for (i = 0; i < elementosPorProcesso; i++) {
        minhaSoma += pow(meusValores[i] - minhaMedia, 2);
    }

    if (meuRank == 0 && resto != 0) {
        double *valoresRestantes = (double*)malloc(resto * sizeof(double));
        for (i = numProcessos * elementosPorProcesso; i < numProcessos * elementosPorProcesso + resto; i++) {
            valoresRestantes[i - numProcessos * elementosPorProcesso] = valores[i];
        }
        double mediaRestantes = calcularMedia(valoresRestantes, resto);
        double somaRestantes = 0.0;
        for (i = 0; i < resto; i++) {
            somaRestantes += pow(valoresRestantes[i] - mediaRestantes, 2);
        }
        minhaSoma += somaRestantes;
        free(valoresRestantes);
    }

    double *somas = NULL;
    if (meuRank == 0) {
        somas = (double*)malloc(numProcessos * sizeof(double));
    }
    MPI_Gather(&minhaSoma, 1, MPI_DOUBLE, somas, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (meuRank == 0) {
        double somaTotal = 0.0;
        for (i = 0; i < numProcessos; i++) {
            somaTotal += somas[i];
        }
        media = calcularMedia(valores, elementosPorProcesso * numProcessos + resto);
        desvioPadrao = sqrt(somaTotal / (elementosPorProcesso * numProcessos + resto));
        printf("A média é %.2lf e o desvio padrão é %.2lf\n", media, desvioPadrao);
        free(valores);
        free(somas);
    }

    free(meusValores);
    MPI_Finalize();

    return 0;
}