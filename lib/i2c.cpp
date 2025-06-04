//
// Created by 0x1iii1ii on 6/4/2025.
//

#include "i2c.h"

I2C::I2C(int bus, uint8_t dev_addr)
    : _fd(-1), _bus(bus), _addr(dev_addr)
{
    int n = std::snprintf(_devicePath, sizeof(_devicePath), "/dev/i2c-%d", _bus);
    if (n < 0 || n >= (int)sizeof(_devicePath)) {
        _fd = -1;
        return;
    }

    _fd = ::open(_devicePath, O_RDWR);
    if (_fd < 0) {
        std::perror("I2C: open failed");
        return;
    }

    if (::ioctl(_fd, I2C_SLAVE, _addr) < 0) {
        std::perror("I2C: ioctl(I2C_SLAVE) failed");
        ::close(_fd);
        _fd = -1;
        return;
    }
}

I2C::~I2C()
{
    if (_fd >= 0) {
        ::close(_fd);
        _fd = -1;
    }
}

bool I2C::ok() const
{
    return (_fd >= 0);
}

bool I2C::setAddress(uint8_t new_addr)
{
    if (_fd < 0) {
        return false;
    }
    if (new_addr == _addr) {
        return true;
    }
    if (::ioctl(_fd, I2C_SLAVE, new_addr) < 0) {
        std::perror("I2C: ioctl(I2C_SLAVE) failed in setAddress");
        return false;
    }
    _addr = new_addr;
    return true;
}

bool I2C::write(const uint8_t* data, int16_t len)
{
    if (_fd < 0 || data == nullptr || len <= 0) {
        return false;
    }
    ssize_t written = ::write(_fd, data, (size_t)len);
    if (written < 0) {
        std::perror("I2C: write failed");
        return false;
    }
    return (written == len);
}

bool I2C::read(uint8_t* data, int16_t len)
{
    if (_fd < 0 || data == nullptr || len <= 0) {
        return false;
    }
    ssize_t rd = ::read(_fd, data, (size_t)len);
    if (rd < 0) {
        std::perror("I2C: read failed");
        return false;
    }
    return (rd == len);
}