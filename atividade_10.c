#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size, i, num_points, count = 0, total_count;
    double x, y, pi_estimate;
    long seed;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // número de pontos a serem gerados por processo
    num_points = 1000000 / size;

    // seed para gerar números aleatórios diferente em cada processo
    seed = rank + 1;

    // gerar pontos aleatórios e contar quantos caem dentro do círculo
    for (i = 0; i < num_points; i++) {
        x = (double)rand_r(&seed) / RAND_MAX * 2 - 1;
        y = (double)rand_r(&seed) / RAND_MAX * 2 - 1;

        if (sqrt(x * x + y * y) <= 1) {
            count++;
        }
    }

    // somar o total de pontos dentro do círculo de todos os processos
    MPI_Reduce(&count, &total_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // calcular a aproximação de Pi
    if (rank == 0) {
        pi_estimate = 4.0 * total_count / (num_points * size);
        printf("Valor aproximado de Pi: %f\n", pi_estimate);
    }

    MPI_Finalize();
    return 0;
}
