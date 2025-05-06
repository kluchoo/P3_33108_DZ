#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <chrono>
#include <assert.h>
#include <windows.h>
#include <omp.h>

void wait(int x) {
    Sleep(x);
}

int main() {
    int32_t i;
    uint32_t n = 10;
    auto start = std::chrono::high_resolution_clock::now();
#pragma omp parallel num_threads(2) default(shared) private(i)
    {
#pragma omp sections nowait
        {
#pragma omp section
            {
                wait(2000);
                printf("Sections - Thread %d working...\n", omp_get_thread_num());
            }

#pragma omp section
            {
                wait(4000);
                printf("Sections - Thread %d working...\n", omp_get_thread_num());
            }
        }
#pragma omp for
        for (i = 0; i < n; i++) {
            printf("Iteration %d execute thread %d.\n", i, omp_get_thread_num());
            wait(400);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    printf("Parallel normal way %llu ms\r\n",
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    int thread_counts[] = {2, 4, 8};
    for (int t = 0; t < 3; ++t) {
        int threads = thread_counts[t];
        // --- Z nowait ---
        start = std::chrono::high_resolution_clock::now();
#pragma omp parallel num_threads(threads) default(shared) private(i)
        {
#pragma omp sections nowait
            {
#pragma omp section
                {
                    wait(2000);
                    printf("[nowait] Sections - Thread %d working...\n", omp_get_thread_num());
                }
#pragma omp section
                {
                    wait(4000);
                    printf("[nowait] Sections - Thread %d working...\n", omp_get_thread_num());
                }
            }
#pragma omp for
            for (i = 0; i < n; i++) {
                printf("[nowait] Iteration %d execute thread %d.\n", i, omp_get_thread_num());
                wait(400);
            }
        }
        end = std::chrono::high_resolution_clock::now();
        printf("Parallel (nowait, %d threads): %llu ms\r\n",
            threads,
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

        // --- Bez nowait ---
        start = std::chrono::high_resolution_clock::now();
#pragma omp parallel num_threads(threads) default(shared) private(i)
        {
#pragma omp sections // bez nowait
            {
#pragma omp section
                {
                    wait(2000);
                    printf("[wait] Sections - Thread %d working...\n", omp_get_thread_num());
                }
#pragma omp section
                {
                    wait(4000);
                    printf("[wait] Sections - Thread %d working...\n", omp_get_thread_num());
                }
            }
#pragma omp for
            for (i = 0; i < n; i++) {
                printf("[wait] Iteration %d execute thread %d.\n", i, omp_get_thread_num());
                wait(400);
            }
        }
        end = std::chrono::high_resolution_clock::now();
        printf("Parallel (wait, %d threads): %llu ms\r\n",
            threads,
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
    }

    return 0;
}