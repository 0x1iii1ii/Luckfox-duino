//
// Created by 0x1iii1ii on 6/4/2025.
//

#include "adc.h"

ADC::ADC(const std::string& dir)
	: _dir(dir){
    _paths[CH0]   = _dir + "/in_voltage0_raw";
    _paths[CH1]   = _dir + "/in_voltage1_raw";
    _scale_path   = _dir + "/in_voltage_scale";

    _fd_raw[CH0] = ::open(_paths[CH0].c_str(), O_RDONLY);
    _fd_raw[CH1] = ::open(_paths[CH1].c_str(), O_RDONLY);
    _fd_scale    = ::open(_scale_path.c_str(), O_RDONLY);

    if (_fd_raw[CH0] < 0 ||
        _fd_raw[CH1] < 0 ||
        _fd_scale  < 0)
    {
        int e0 = errno;
        if (_fd_raw[CH0] >= 0) ::close(_fd_raw[CH0]);
        if (_fd_raw[CH1] >= 0) ::close(_fd_raw[CH1]);
        if (_fd_scale  >= 0) ::close(_fd_scale);
        throw std::runtime_error(
            std::string("ADC initialization failed: ") + std::strerror(e0));
    }
}

ADC::~ADC() {
    if (_fd_raw[CH0] >= 0) ::close(_fd_raw[CH0]);
    if (_fd_raw[CH1] >= 0) ::close(_fd_raw[CH1]);
    if (_fd_scale    >= 0) ::close(_fd_scale);
}

/// Read the raw integer value from channel 0 or 1.
/// Returns -1 on error.
int ADC::readRaw(Channel ch) {
    if (ch != CH0 && ch != CH1) {
        return -1;
    }

    int fd = _fd_raw[ch];
    if (fd < 0) {
        return -1;
    }

    if (lseek(fd, 0, SEEK_SET) < 0) {
        return -1;
    }

    char buf[32] = {0};
    ssize_t n = ::read(fd, buf, sizeof(buf) - 1);
    if (n <= 0) {
        return -1;
    }
    buf[n] = '\0';
    return std::atoi(buf);
}

/// Read the scale (float) from in_voltage_scale.
/// Returns negative on error.
float ADC::readScale() {
    if (_fd_scale < 0) {
        return -1.0f;
    }
    if (lseek(_fd_scale, 0, SEEK_SET) < 0) {
        return -1.0f;
    }

    char buf[32] = {0};
    ssize_t n = ::read(_fd_scale, buf, sizeof(buf) - 1);
    if (n <= 0) {
        return -1.0f;
    }
    buf[n] = '\0';
    return std::strtof(buf, nullptr);
}

/// Compute voltage (in volts) = raw * scale / 1000.0
/// Returns negative on error.
float ADC::readVoltage(Channel ch) {
    int raw = readRaw(ch);
    if (raw < 0) {
        return -1.0f;
    }
    float scale = readScale();
    if (scale < 0.0f) {
        return -1.0f;
    }
    return (raw * scale) / 1000.0f;
}