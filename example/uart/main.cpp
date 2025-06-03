#include <iostream>
#include "uart.h"

UART testSerial("/dev/ttyS3", B115200);

void serialRead(const std::string &rawdata)
{
    std::cout << "\nSerial Received: " << rawdata << std::endl;
}

int main() {

    std::cout << "Hello and welcome to uart serial example" << "!\n";
    std::cout << "Using UART3 (/dev/ttyS3)" <<  std::endl;
    if (!testSerial.isOpen()) {
        std::cerr << "Failed to open serial port /dev/ttyS3" << std::endl;
        return 1;
    }
    std::cout << "Serial port started!" << std::endl;
    testSerial.writeSerial("hello from luckfox serial!\r\n");
    testSerial.setDataReceivedCallback(serialRead);
    // Start background reading
    testSerial.startReading();
    std::string userInput;
    while (1)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // debounce delay
        std::cout << "Enter message (type 'q' to quit): ";
        std::getline(std::cin, userInput);
        if (userInput == "q") {
            break;
        }
        testSerial.writeSerial(userInput + "\r\n");
    }
    testSerial.stopReading();
    return 0;
}