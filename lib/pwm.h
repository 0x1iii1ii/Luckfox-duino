//
// Created by 0x1iii1ii on 6/3/2025.
//

#ifndef PWM_H
#define PWM_H

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "pwm_def.h"

#define NORMAL "normal"
#define REVERSE "inversed"
#define PERIOD_NS 1000000
#define MIN_DUTY_NS 0
#define MAX_DUTY_NS PERIOD_NS
#define MAX_8BIT 255

class PWM {
  private:
    int pin;
    bool initialized;
    char pwm_path[50];
    char pwm_duty[50];
    std::string periodPath() const;
    std::string enablePath() const;
    std::string exportPath() const;
    std::string polarityPath() const;
    std::string unexportPath() const;

  public:
    PWM(int pinNumber);
    ~PWM(void);
    void begin(int period, const char* polarity);
    void begin(void);
    void writeSysfs(const std::string &path, const std::string &value);
    bool setPolarity(const char* polarity);
    bool setEnable(bool enable);
    bool setPeriod(unsigned int period);
    // Write an 8-bit value 0..255 ⇒ duty_cycle = [0 .. PERIOD_NS]
    // (Arduino: analogWrite(pin, value))
    void analogWrite(int value);
    void analogWrite8bit(int value);
    // Write LOW (0) or HIGH (1) ⇒ duty_cycle = 0 or PERIOD_NS
    // (Arduino: digitalWrite(pin, LOW/HIGH))
    void digitalWrite(int level);
    // Internal: write raw duty_cycle in nanoseconds
    void setDutyCycleNs(int duty_ns);
};

#endif //PWM_H
