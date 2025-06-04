//
// Created by 0x1iii1ii on 6/3/2025.
//

#ifndef PWM_H
#define PWM_H

#include <array>
#include <chrono>
#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <stdexcept>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>
#include "pwm_def.h"

#define NORMAL "normal"
#define REVERSE "inversed"
#define DEFAULT_PERIOD_NS 1000000
#define MIN_DUTY_NS 0
#define MAX_DUTY_NS DEFAULT_PERIOD_NS
#define MIN_PERIOD_NS 1000      // 1 µs
#define MAX_PERIOD_NS 100000000 // 100 ms
#define MAX_8BIT 255

class PWM {
private:
  const int           _pin;
  const std::string   _basePath;
  const std::string   _exportPath;
  const std::string   _unexportPath;
  const std::string   _pwmDir;
  const std::string   _periodPath;
  const std::string   _dutyPath;
  const std::string   _enablePath;
  const std::string   _polarityPath;

  int _fd_period;
  int _fd_duty;
  int _fd_enable;
  int _fd_polarity;

  bool _initialized;

public:
    explicit PWM(int pinNumber);
    ~PWM();
    void begin(int period, const char* polarity);
    void begin();
    void setPolarity(const char* polarity);
    void setPeriod(int period_ns);
    // Write an 8-bit value 0..255 ⇒ duty_cycle = [0 .. PERIOD_NS]
    void analogWrite(int value);
    void analogWrite8bit(int value);
    // Write LOW (0) or HIGH (1) ⇒ duty_cycle = 0 or PERIOD_NS
    void digitalWrite(int level);
    // Internal: write raw duty_cycle in nanoseconds
    void setDutyCycleNs(int duty_ns);

    /// Helper: write a C‐string (e.g. "normal" or "inversed") to fd, after seeking to 0.
    static bool writeString(int fd, const char* s) {
        if (fd < 0) return false;
        if (lseek(fd, 0, SEEK_SET) < 0) return false;
        ssize_t len = std::strlen(s);
        return (::write(fd, s, len) == len);
    }

    /// Helper: write an integer (in decimal) to fd, after seeking to 0.
    static bool writeInteger(int fd, int value) {
        if (fd < 0) return false;
        if (lseek(fd, 0, SEEK_SET) < 0) return false;
        // Use a small stack buffer; PWM sysfs only needs a few digits.
        char buf[32];
        int n = std::snprintf(buf, sizeof(buf), "%d", value);
        if (n < 1) return false;
        return (::write(fd, buf, static_cast<size_t>(n)) == n);
    }

    /// Close any open file descriptors.
    void cleanupFileDescriptors() {
        if (_fd_period >= 0)   ::close(_fd_period);
        if (_fd_duty   >= 0)   ::close(_fd_duty);
        if (_fd_enable >= 0)   ::close(_fd_enable);
        if (_fd_polarity >= 0) ::close(_fd_polarity);
        _fd_period = _fd_duty = _fd_enable = _fd_polarity = -1;
    }
};

#endif //PWM_H
