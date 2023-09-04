#include <stdio.h>
#include <omp.h>

static long num_steps = 2000000000;  // 2e09
double step;

#define PAD 8 // Assume 64 byte L1 cache line size
#define NUM_THREADS 2 // Start with 2 threads; you'll change this later.

int main() {
    int i, nthreads;
    double pi;
    double sum[NUM_THREADS][PAD];

    step = 1.0 / (double) num_steps;

    omp_set_num_threads(NUM_THREADS);
    #pragma omp parallel
    {
        int i, id, nthrds;
        double x;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        if (id == 0) nthreads = nthrds;

        for (i = id, sum[id][0] = 0.0; i < num_steps; i = i + nthrds) {
            x = (i + 0.5) * step;
            sum[id][0] += 4.0 / (1.0 + x * x);
        }
    }

    for (i = 0, pi = 0.0; i < nthreads; i++) pi += sum[i][0] * step;

    printf("Pi = %f\n", pi);
    return 0;
}

