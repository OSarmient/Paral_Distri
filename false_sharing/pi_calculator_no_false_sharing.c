#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

static long num_steps = 2000000000; // 2e09
double step;

#define PAD 8
#define NUM_THREADS 2

int main() {
    int i, nthreads;
    double pi;
    double *sum;

    // Alocar memoria para el arreglo sum con padding
    sum = (double *) malloc(NUM_THREADS * PAD * sizeof(double));
    if (sum == NULL) {
        printf("Error: No se pudo alocar memoria para el arreglo sum\n");
        return 1;
    }

    step = 1.0 / (double) num_steps;
    omp_set_num_threads(NUM_THREADS);

    double start_time = omp_get_wtime();

    #pragma omp parallel
    {
        int i, id, nthrds;
        double x;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        if (id == 0) nthreads = nthrds;

        double *local_sum = sum + id * PAD;  // Apuntador a la ubicación de sum para este hilo
        *local_sum = 0.0;

        for (i = id; i < num_steps; i += nthrds) {
            x = (i + 0.5) * step;
            *local_sum += 4.0 / (1.0 + x * x);
        }
    }

    for (i = 0, pi = 0.0; i < nthreads; i++) {
        pi += *(sum + i * PAD) * step;
    }

    double run_time = omp_get_wtime() - start_time;

    printf("Pi = %f, Tiempo transcurrido = %f segundos\n", pi, run_time);

    free(sum);  // Liberar memoria
    return 0;
}
