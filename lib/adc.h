//
// Created by 0x1iii1ii on 6/4/2025.
//

#ifndef ADC_H
#define ADC_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <string>
#include <array>
#include <thread>

class ADC {
private:
    std::string                 _dir;
    std::array<std::string, 2>  _paths;
    std::string                 _scale_path;

    int                         _fd_raw[2]   = { -1, -1 };
    int                         _fd_scale    = -1;

public:
    enum Channel { CH0 = 0, CH1 = 1 };
    explicit ADC(const std::string& dir = "/sys/bus/iio/devices/iio:device0");
    ~ADC();
    int readRaw(Channel ch);
    float readScale();
    float readVoltage(Channel ch);
};

#endif //ADC_H
