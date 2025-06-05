//
// Created by 0x1iii1ii on 6/5/2025.
//

#ifndef SPI_H
#define SPI_H

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/spi/spidev.h>
#include <sys/ioctl.h>

#define CONFIG_BITS 8
#define CONFIG_MAX_SPEED_HZ 1000000
#define CONFIG_MODE SPI_MODE_0

class SPI {
private:
  int _fd;
  int _mode;
  int _speed;
  int  _bits;

public:
  SPI(const std::string &device_path = "/dev/spidev0.0",
      int mode = SPI_MODE_0,
      int bits_per_word = CONFIG_BITS,
      int speed_hz = CONFIG_MAX_SPEED_HZ);
  ~SPI();
  bool isOpen() const;
  void write(const uint8_t* tx_buf, size_t len);
  void read(uint8_t* rx_buf, size_t len);
  void transfer(const uint8_t* tx_buf, uint8_t* rx_buf, size_t len);

};

#endif //SPI_H
