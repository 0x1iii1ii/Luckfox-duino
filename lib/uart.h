//
// Created by 0x1iii1ii on 3/6/2025.
//

#ifndef UART_H
#define UART_H

#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>
#include <functional>

class UART {
public:
    // Constructor: Opens the serial port with a specified baud rate (default: 115200)
    UART(const std::string& portName, speed_t baudRate);

    // Destructor: Ensures the port is closed and the reading thread is stopped
    ~UART();
    // Define the callback type using std::function
    using DataReceivedCallback = std::function<void(const std::string&)>;

    // Method to set the callback
    void setDataReceivedCallback(DataReceivedCallback callback) {
        onDataReceived_ = std::move(callback);
    }
    // Check if the serial port is open
    bool isOpen() const {
        return fd_ != -1;
    }

    // Write data to the serial port, returns success/failure
    bool writeSerial(const std::string& data);

    // Read available data from the serial port (non-blocking)
    std::string readSerial();

    // Start a background thread to continuously read from the serial port
    void startReading();

    // Stop the background reading thread
    void stopReading();

private:
    std::string portName_;         // Serial port name (e.g., "/dev/ttyS3")
    int fd_;                       // File descriptor for the serial port
    std::atomic<bool> running_;    // Flag to control the reading thread
    std::thread readerThread_;     // Background thread for reading
    std::mutex mutex_;             // Mutex for thread-safe console output
    DataReceivedCallback onDataReceived_; // Callback function

    // Open and configure the serial port
    void openPort(speed_t baudRate);
};

#endif
