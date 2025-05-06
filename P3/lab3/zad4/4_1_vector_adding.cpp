#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <thread>
#include <chrono>

#define SIZE 100
#define THREAD_COUNT (SIZE / 10)

void add(int id, int* a, int* b, int* c) {
    for (int i = id * 10; i < (id + 1) * 10; ++i) {
        c[i] = a[i] + b[i];
    }
}

int main() {
    srand(time(NULL));
    int a[SIZE];
    int b[SIZE];
    int c[SIZE];

    for (int i = 0;i < SIZE;i++) {
        a[i] = rand() % 100 + 1; //1 do 100
        b[i] = rand() % 100 + 1;
    }

    //wypisanie na ekranie A
    for (int i = 0;i < SIZE;i++) {
        printf("%u ", a[i]);
    }
    printf("\n");

    //wypisanie na ekranie B
    for (int i = 0;i < SIZE;i++) {
        printf("%u ", b[i]);
    }
    printf("\n");

    auto start = std::chrono::high_resolution_clock::now();

    std::thread** threads = new std::thread * [THREAD_COUNT];
    for (int i = 0;i < THREAD_COUNT;i++) {
        threads[i] = new std::thread(add, i, a, b, c); //wykorzystuje i jako id danego wątku
    }

    for (int i = 0;i < THREAD_COUNT;i++) {
        threads[i]->join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    printf("Czas wykonania: %f sekund\n", elapsed.count());

    for (int i = 0;i < THREAD_COUNT;i++) {
        delete threads[i];
    }
    delete[] threads;

    //wypisanie na ekranie C
    for (int i = 0;i < SIZE;i++) {
        printf("%u ", c[i]);
    }

    return 0;
}