#include <cstdio>
#include <thread>
#include <windows.h>
#include <iostream>
#include <vector> // Dodajemy nagłówek dla std::vector

void action(int id) {
    printf("Uruchamiam watek %d\n", id);
    Sleep(5 * 1000); // 5 sekund
    printf("Koncze watek %d\n", id);
}

int main() {
    int thread_count = 8;
    std::cin >> thread_count;

    // Używamy std::vector zamiast tablicy wskaźników
    std::vector<std::thread> threads;

    // Otwieranie wątków
    for (int i = 0; i < thread_count; i++) {
        threads.emplace_back(action, i); // Dodajemy wątki do vectora
    }

    // Wątki pracują, ale trzeba je zsynchronizować
    for (auto& thread : threads) {
        thread.join(); // Czekamy na zakończenie każdego wątku
    }

    // Nie musimy ręcznie zwalniać pamięci, ponieważ std::vector to robi automatycznie

    printf("Koniec programu \r\n");

    return 0;
}