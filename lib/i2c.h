//
// Created by 0x1iii1ii on 6/4/2025.
//

#ifndef I2C_H
#define I2C_H

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <cstdio>
#include <cerrno>
#include <cstring>
#include <cstdint>

class I2C {
public:
    /// Opens "/dev/i2c-<bus>" and sets the slave address to dev_addr.
    /// If opening or ioctl fails, _fd < 0 and ok() returns false.
    I2C(int bus, uint8_t dev_addr);

    /// Closes the I2C file descriptor if open.
    ~I2C();

    /// Returns true if the constructor succeeded in opening the bus and setting the address.
    bool ok() const;

    /// Writes 'len' bytes from data[] to the bus.
    /// Returns true if all bytes were written, false otherwise.
    bool write(const uint8_t* data, int16_t len);

    /// Reads 'len' bytes into data[] from the bus.
    /// Returns true if all bytes were read, false otherwise.
    bool read(uint8_t* data, int16_t len);

    /// Change the I2C slave address (uses ioctl).
    /// Returns true on success, false on failure.
    bool setAddress(uint8_t new_addr);
private:
    int      _fd;             ///< File descriptor for /dev/i2c-<bus>
    int      _bus;            ///< I2C bus number
    uint8_t  _addr;           ///< Current slave address
    char     _devicePath[32]; ///< "/dev/i2c-<bus>"
};

#endif //I2C_H
