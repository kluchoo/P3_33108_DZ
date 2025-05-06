#include <thread>
#include <cstdio>
#include <windows.h>
#include <cstdlib>
#include <ctime>

unsigned int counter = 0;

void increment(int id)
{
    for (int i = 0; i < 10; i++)
    {
        counter++;
        Sleep(300);
    }

    // ten blok wykona się tylko raz mimo, że wątków jest więcej
    if (id == 1)
    {
        printf("%u\n", counter);
    }
}

void sumArraySegment(int id, int *array)
{
    int local_sum = 0;
    thread_local int thread_local_sum = 0;

    for (int i = id * 10; i < (id + 1) * 10; i++)
    {
        local_sum += array[i];
        thread_local_sum += array[i];
    }

    printf("Watek %d: Suma lokalna = %d, Suma thread_local = %d\n", id, local_sum, thread_local_sum);
    printf("%d -> %d\n", id, local_sum); // Wypisanie id -> wartość
}

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    // Alokacja tablicy
    int *array = new int[100];

    // Wypełnienie tablicy losowymi liczbami z zakresu 1-10
    for (int i = 0; i < 100; i++)
    {
        array[i] = rand() % 10 + 1;
    }

    // Wypisanie zawartości tablicy
    printf("Zawartosc tablicy:\n");
    for (int i = 0; i < 100; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

    // Alokacja 10 wątków
    std::thread threads[10];
    for (int i = 0; i < 10; i++)
    {
        threads[i] = std::thread(sumArraySegment, i, array);
    }

    // Dołączenie wątków
    for (int i = 0; i < 10; i++)
    {
        threads[i].join();
    }

    std::thread t1(increment, 1);
    std::thread t2(increment, 2);

    t1.join();
    t2.join();

    delete[] array; // Zwolnienie pamięci

    return 0;
}
