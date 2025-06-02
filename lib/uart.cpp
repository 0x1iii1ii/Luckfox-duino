//
// Created by 0x1iii1ii on 6/2/2025.
//

#include "uart.h"

// Constructor: Opens the serial port with a specified baud rate (default: 115200)
UART::UART(const std::string& portName, speed_t baudRate = B115200)
        : portName_(portName), fd_(-1), running_(false) {
    openPort(baudRate);
}

// Destructor: Ensures the port is closed and the reading thread is stopped
UART::~UART() {
    stopReading();
    if (fd_ != -1) {
        close(fd_);
    }
}

void UART::stopReading ()  {
    if (running_.load()) {
        running_.store(false);
        if (readerThread_.joinable()) {
            readerThread_.join();
        }
    }
}

void UART::startReading () {
    if (!running_.load()) {
        running_.store(true);
        readerThread_ = std::thread([this]() {
            while (running_.load()) {
                std::string response = readSerial();
                if (!response.empty()) {
                    std::lock_guard<std::mutex> lock(mutex_);
                    onDataReceived_(response);
                    std::cout << "\nReceived: " << response << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        });
    }
}

bool UART::writeSerial(const std::string& data)  {
    if (fd_ != -1) {
        ssize_t n = write(fd_, data.c_str(), data.size());
        if (n < 0) {
            std::cerr << "Error writing to " << portName_ << ": "
                      << strerror(errno) << std::endl;
            return false;
        }
        return true;
    }
    return false;
}

std::string UART::readSerial() {
    std::string result;
    if (fd_ != -1) {
        char buf[256];
        ssize_t n = read(fd_, buf, sizeof(buf));
        if (n > 0) {
            result.assign(buf, n);
        }
    }
    return result;
}

void UART::openPort(speed_t baudRate) {
    fd_ = open(portName_.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
    if (fd_ < 0) {
        std::cerr << "Error opening " << portName_ << ": "
                  << strerror(errno) << std::endl;
        return;
    }

    struct termios tty;
    if (tcgetattr(fd_, &tty) != 0) {
        std::cerr << "Error from tcgetattr: "
                  << strerror(errno) << std::endl;
        close(fd_);
        fd_ = -1;
        return;
    }

    // Set baud rates
    cfsetospeed(&tty, baudRate);
    cfsetispeed(&tty, baudRate);

    // Configure 8N1 (8-bit, no parity, 1 stop bit)
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;  // 8-bit characters
    tty.c_cflag &= ~(PARENB | PARODD);           // No parity
    tty.c_cflag &= ~CSTOPB;                      // 1 stop bit
    tty.c_cflag &= ~CRTSCTS;                     // No hardware flow control

    // Disable software flow control
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    // Enable receiver, ignore modem control lines
    tty.c_cflag |= (CLOCAL | CREAD);
    // Disable break processing, canonical mode, echo, and signals
    tty.c_iflag &= ~IGNBRK;
    tty.c_lflag = 0;  // Non-canonical mode
    tty.c_oflag = 0;  // No output processing

    // Non-blocking read with 0.5s timeout
    tty.c_cc[VMIN] = 0;   // Return immediately if no data
    tty.c_cc[VTIME] = 5;  // 0.5 seconds timeout

    if (tcsetattr(fd_, TCSANOW, &tty) != 0) {
        std::cerr << "Error from tcsetattr: "
                  << strerror(errno) << std::endl;
        close(fd_);
        fd_ = -1;
    }
}
