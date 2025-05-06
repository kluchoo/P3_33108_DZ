#include <chrono>
#include <cstdio>
#include <iostream>
#include <fstream>
// #include <windows.h>
using namespace std;

int main(){
    auto start = std::chrono::steady_clock::now();

    long long fib[500000];
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i < 500000; ++i) {
        fib[i] = fib[i-1] + fib[i-2];
    }

    auto end = std::chrono::steady_clock::now();

    cout << "Czas trwania: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << endl;
    cout << "\nfib[30] = " << fib[30] << endl;
    return 0;
}
