//
// Created by 0x1iii1ii on 3/12/2025.
//

#ifndef GPIO_H
#define GPIO_H

#include <chrono>
#include <fstream>
#include <cstdlib>
#include <thread>
#include "gpio_def.h"

#define HIGH 1
#define LOW  0
#define INPUT  "in"
#define OUTPUT "out"

class GPIO {
private:
    int pin;                   // GPIO pin number
    char value_path[50];       // Path to the GPIO value file
    char direction_path[50];   // Path to the GPIO direction file
    FILE *value_file;          // File pointer for value
    bool initialized;          // Tracks if the pin is initialized
    // Helper function to export the GPIO pin
    bool exportPin();
    // Helper function to unexport the GPIO pin
    bool unexportPin();

public:
    GPIO(int pinNumber);
    ~GPIO(void);
    // pinMode: Set the pin as INPUT or OUTPUT
    bool pinMode(const char* mode);
    // digitalWrite: Write HIGH (1) or LOW (0) to the pin
    bool digitalWrite(int value);
    // digitalRead: Read the current value of the pin (0 or 1)
    int digitalRead();
    bool waitForValue(int targetValue, std::chrono::milliseconds timeout);
};


#endif //GPIO_H
