#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 1000

int main(int argc, char** argv) {
    int rank, size, i;
    int array[ARRAY_SIZE];
    int sum = 0, double_sum = 0;
    int recv_buf[2];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // preenche o vetor com valores aleatórios
        for (i = 0; i < ARRAY_SIZE; i++) {
            array[i] = rand() % 10;
        }

        // envia o vetor por broadcast para os processos 1 e 2
        MPI_Bcast(array, ARRAY_SIZE, MPI_INT, 0, MPI_COMM_WORLD);

        // recebe os resultados dos processos 1 e 2
        MPI_Recv(&recv_buf, 2, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        sum = recv_buf[0];
        double_sum = recv_buf[1];

        MPI_Recv(&recv_buf, 2, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        sum += recv_buf[0];
        double_sum += recv_buf[1];

        // mostra os resultados na tela
        printf("Resultado 1: %d\n", sum);
        printf("Resultado 2: %d\n", double_sum);
    } else if (rank == 1) {
        // recebe o vetor do processo 0
        MPI_Bcast(array, ARRAY_SIZE, MPI_INT, 0, MPI_COMM_WORLD);

        // calcula o somatório dos elementos do vetor
        for (i = 0; i < ARRAY_SIZE; i++) {
            sum += array[i];
        }

        // envia o resultado para o processo 0
        MPI_Send(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else if (rank == 2) {
        // recebe o vetor do processo 0
        MPI_Bcast(array, ARRAY_SIZE, MPI_INT, 0, MPI_COMM_WORLD);

        // calcula o somatório do dobro de cada elemento do vetor
        for (i = 0; i < ARRAY_SIZE; i++) {
            double_sum += 2 * array[i];
        }

        // envia o resultado para o processo 0
        MPI_Send(&double_sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
