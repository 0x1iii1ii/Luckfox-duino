//
// Created by 0x1iii1ii on 6/5/2025.
//

#include "spi.h"

SPI::SPI(const std::string &device_path,
              int mode,
              int bits_per_word,
              int speed_hz)
    : _fd(-1), _mode(mode), _bits(bits_per_word), _speed(speed_hz) {
    /// Open and configure the SPI device.
    /// @param device_path e.g. "/dev/spidev0.0"
    /// @param mode        SPI mode (SPI_MODE_0, SPI_MODE_1, etc.)
    /// @param bits_per_word  Bits per word (typically 8)
    /// @param speed_hz    Clock speed in Hz
    _fd = ::open(device_path.c_str(), O_RDWR);
    if (_fd < 0) {
      perror("Failed to open device");
      return;
    }
    // config
    if(::ioctl(_fd, SPI_IOC_WR_MODE, _mode) < 0 ){
      perror("Failed to set spi mode");
      ::close(_fd);
      return;
    }
    if(::ioctl(_fd, SPI_IOC_WR_BITS_PER_WORD, _bits) < 0 ) {
      perror("Failed to get spi bit per word");
      ::close(_fd);
      return;
    }
    if(::ioctl(_fd, SPI_IOC_WR_MAX_SPEED_HZ, _speed) < 0 ) {
      perror("Failed to set max speed hz");
      ::close(_fd);
      return;
    }
}

SPI::~SPI() {
  if(_fd >= 0) {
    ::close(_fd);
    _fd = -1;
  }
}

/// Write-only transfer (ignores read data).
void SPI::write(const uint8_t* tx_buf, size_t len) {
  if (_fd < 0) {
    perror("device not opened");
  }
  if (len == 0) {
    return;
  }
  ssize_t ret = ::write(_fd, tx_buf, len);
  if (ret < 0 || static_cast<size_t>(ret) != len) {
    perror("Failed to write to device");
  }
}

/// Read-only transfer (sends dummy 0x00 bytes).
void SPI::read(uint8_t* rx_buf, size_t len) {
  if (_fd < 0) {
    perror("device not opened");
  }
  if (len == 0) {
    return;
  }
  // Create a temporary TX buffer filled with 0x00
  static const uint8_t DUMMY_TX = 0x00;
  struct spi_ioc_transfer tr;
  std::memset(&tr, 0, sizeof(tr));
  tr.tx_buf        = reinterpret_cast<unsigned long>(&DUMMY_TX);
  tr.rx_buf        = reinterpret_cast<unsigned long>(rx_buf);
  tr.len           = static_cast<uint32_t>(len);
  tr.delay_usecs   = 0;
  tr.speed_hz      = _speed;
  tr.bits_per_word = _bits;

  int ret = ::ioctl(_fd, SPI_IOC_MESSAGE(1), &tr);
  if (ret < 0) {
    perror("Failed to read from device");
  }
}

/// Returns true if the device is open and configured correctly.
bool SPI::isOpen() const {
  return (_fd >= 0);
}

/// Perform a full-duplex SPI transfer of `len` bytes.
/// `tx_buf` and `rx_buf` must each be at least `len` bytes long.
/// Throws on error.
void SPI::transfer(const uint8_t* tx_buf, uint8_t* rx_buf, size_t len) {
  if (_fd < 0) {
    perror("device not opened");
  }
  if (len == 0) {
    return;
  }

  struct spi_ioc_transfer tr;
  std::memset(&tr, 0, sizeof(tr));
  tr.tx_buf        = reinterpret_cast<unsigned long>(tx_buf);
  tr.rx_buf        = reinterpret_cast<unsigned long>(rx_buf);
  tr.len           = static_cast<uint32_t>(len);
  tr.delay_usecs   = 0;
  tr.speed_hz      = _speed;
  tr.bits_per_word = _bits;

  int ret = ::ioctl(_fd, SPI_IOC_MESSAGE(1), &tr);
  if (ret < 0) {
    perror("error: SPI_IOC_MESSAGE failed");
  }
  // ret should equal number of bytes transferred if successful
}