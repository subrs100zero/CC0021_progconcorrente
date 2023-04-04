#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#define num_steps 300000000
int main(){
    double step;
    double x,pi,sum;

    step = 1.0/(double)num_steps;

    double inicio_P = omp_get_wtime();
    pi = 0.0;
    #pragma omp_parallel_num_threads(4)
    {
        double x = 0.0, sum = 0.0;
        int i,id,nthreads;
        id = omp_get_thread_num();
        nthreads = omp_get_num_threads();
        for(i = id, sum = 0.0; i<num_steps; i = i + nthreads){
            x = (i+0.5)*step;
            sum = sum+4.0/(1.0+x*x);
        }
    }
    double fim_P = omp_get_wtime();
    double tempo_P = fim_P - inicio_P;
    printf("Pi: %f\n",pi);
    printf("Execucao paralela(s): %f\n",tempo_P);    
    return 0;
}