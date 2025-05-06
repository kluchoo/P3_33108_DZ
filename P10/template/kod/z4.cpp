#include <cstdio>
#include <cmath>
#include <omp.h>

int main() {
    const int N = 8;
    double v[N] = {1, 2, 3, 4, 5, 6, 7, 8};
    double sum[4] = {0, 0, 0, 0};

#pragma omp parallel sections num_threads(4)
    {
#pragma omp section
        for (int i = 0; i < 2; ++i) sum[0] += v[i] * v[i];
#pragma omp section
        for (int i = 2; i < 4; ++i) sum[1] += v[i] * v[i];
#pragma omp section
        for (int i = 4; i < 6; ++i) sum[2] += v[i] * v[i];
#pragma omp section
        for (int i = 6; i < 8; ++i) sum[3] += v[i] * v[i];
    }
    double total = sum[0] + sum[1] + sum[2] + sum[3];
    printf("Dlugosc wektora: %f\n", sqrt(total));
    return 0;
}
