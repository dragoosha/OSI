#include <Windows.h>
#include <iostream>
#include <csignal>
#include <cstdlib>


void signalHandler(int signal) {
    std::cout << "Процесс получил сигнал: " << signal << std::endl;
    exit(signal);
}

int main() {
    signal(SIGINT, signalHandler); 
    signal(SIGTERM, signalHandler);

    std::cout << "Процесс ожидает сигнал о завершении работы..." << std::endl;

    while (true) {
        Sleep(1);
    }

    return 0;
}
