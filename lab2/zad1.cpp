#include <cstdio>
#include <thread>
#include <windows.h>
#include <iostream>

int action(int id, int czas) {
    std::thread::id this_id = std::this_thread::get_id();
    std::cout << "Uruchamiam watek: " << id << " " << this_id << "\n";

    Sleep(czas * 1000); //10 sekund
    printf("Koncze watek %d\n", id);
    return 0;
}

int main() {
    //tworzenie wątku
    std::thread t1(action, 1, 10); //konstruktor klasy t1 przyjmuje minimum wskaźnik na funckje do wykonania
    std::thread t2(action, 2, 5); //funckja ta może coś zwracać, ale może zwaracać też void
    std::thread t3(action, 3, 6); //dalsze parametry zostaną przekazane do podanej funckji

    t1.join();  //synchronizacja
    t2.join();  //wątek główny ma tu poczekać na te 3 wątki
    t3.join();  //inaczej program by się zakończył wcześniej bo wątki trwają minimum 10 sekund

    printf("Koniec programu \r\n");

    return 0;
}