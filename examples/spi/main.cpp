#include <iostream>
#include "spi.h"
#include <thread>

SPI mySPI;

int main() {

    std::cout << "Hello and welcome to SPI example" << "!\n";
    while (1)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return 0;
}