//
// Created by 0x1iii1ii on 6/2/2025.
//
#include "gpio.h"

// Constructor
GPIO::GPIO(int pinNumber) {
    pin = pinNumber;
    snprintf(direction_path, sizeof(direction_path), "/sys/class/gpio/gpio%d/direction", pin);
    snprintf(value_path, sizeof(value_path), "/sys/class/gpio/gpio%d/value", pin);
    value_file = NULL;
    initialized = false;
}

// Destructor to clean up
GPIO::~GPIO(void) {
    if (initialized) {
        if (value_file != NULL) {
            fclose(value_file);
        }
        unexportPin();
    }
}

bool GPIO::exportPin(void)  {
    FILE *export_file = fopen("/sys/class/gpio/export", "w");
    if (export_file == NULL) {
        perror("Failed to open GPIO export file");
        return false;
    }
    fprintf(export_file, "%d", pin);
    fclose(export_file);
    return true;
}

bool GPIO::unexportPin(void)  {
    FILE *unexport_file = fopen("/sys/class/gpio/unexport", "w");
    if (unexport_file == NULL) {
        perror("Failed to open GPIO unexport file");
        return false;
    }
    fprintf(unexport_file, "%d", pin);
    fclose(unexport_file);
    return true;
}

bool GPIO::pinMode(const char* mode)  {
    if (!initialized) {
        if (!exportPin()) {
            return false;
        }
        initialized = true;
    }

    FILE *direction_file = fopen(direction_path, "w");
    if (direction_file == NULL) {
        perror("Failed to open GPIO direction file");
        return false;
    }
    fprintf(direction_file, "%s", mode); // "in" or "out"
    fclose(direction_file);
    return true;
}

bool GPIO::digitalWrite(int value)  {
    if (!initialized) {
        perror("Pin not initialized. Call pinMode first.");
        return false;
    }

    if (value_file == NULL) {
        value_file = fopen(value_path, "w");
        if (value_file == NULL) {
            perror("Failed to open GPIO value file");
            return false;
        }
    }

    fprintf(value_file, "%d", value);
    fflush(value_file);
    return true;
}

int GPIO::digitalRead(void)  {
    if (!initialized) {
        perror("Pin not initialized. Call pinMode first.");
        return -1;
    }

    FILE *read_file = fopen(value_path, "r");
    if (read_file == NULL) {
        perror("Failed to open GPIO value file for reading");
        return -1;
    }

    int value;
    fscanf(read_file, "%d", &value);
    fclose(read_file);
    return value;
}

bool GPIO::waitForValue(int targetValue, std::chrono::milliseconds timeout)  {
    auto start = std::chrono::steady_clock::now();
    FILE* file = fopen(value_path, "r");
    if (file == nullptr) {
        perror("Failed to open GPIO value file");
        return false;
    }
    bool found = false;
    while (std::chrono::steady_clock::now() - start < timeout) {
        rewind(file); // Reset file pointer to read current value
        int currentValue;
        if (fscanf(file, "%d", &currentValue) == 1) {
            if (currentValue == targetValue) {
                found = true;
                break;
            }
        }
        std::this_thread::sleep_for(std::chrono::microseconds(100)); // Sleep 100µs
    }
    fclose(file);
    return found;
}