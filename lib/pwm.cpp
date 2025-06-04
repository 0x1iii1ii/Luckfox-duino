//
// Created by 0x1iii1ii on 6/3/2025.
//

#include "pwm.h"

PWM::PWM(int pinNumber)
    : _pin(pinNumber),
      _basePath("/sys/class/pwm/pwmchip" + std::to_string(pinNumber)),
      _exportPath(_basePath + "/export"),
      _unexportPath(_basePath + "/unexport"),
      _pwmDir (_basePath + "/pwm0"),
      _periodPath ( _pwmDir + "/period"      ),
      _dutyPath   ( _pwmDir + "/duty_cycle"  ),
      _enablePath ( _pwmDir + "/enable"      ),
      _polarityPath(_pwmDir + "/polarity"    ),
      _fd_period  (-1),
      _fd_duty    (-1),
      _fd_enable  (-1),
      _fd_polarity(-1),
      _initialized(false)
    {
    int fd_exp = ::open(_exportPath.c_str(), O_WRONLY);
    if (fd_exp < 0) {
        throw std::runtime_error(std::string("PWM::constructor: failed to open export: ") +
            std::strerror(errno));
    }
    if (::dprintf(fd_exp,"0") < 0) {
        ::close(fd_exp);
        throw std::runtime_error(std::string("PWM::constructor: failed to open export: ") +
            std::strerror(errno));
    }
    ::close(fd_exp);

    // wait till dir pwm0 to appear under sysfs
    for (int attempt = 0; attempt < 50; attempt++) {
        struct stat st;
        if (stat(_pwmDir.c_str(), &st) == 0 && S_ISDIR(st.st_mode)) {
            break;
        }
        // Sleep 10 ms, then retry
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if (attempt == 49) {
            throw std::runtime_error(
                std::string("PWM::constructor: pwm0 directory never appeared after export"));
        }
    }
    // open each pwm attributes files
    _fd_period   = ::open(_periodPath.c_str(),   O_WRONLY);
    _fd_duty     = ::open(_dutyPath.c_str(),     O_WRONLY);
    _fd_enable   = ::open(_enablePath.c_str(),   O_WRONLY);
    _fd_polarity = ::open(_polarityPath.c_str(), O_WRONLY);

    if ((_fd_period < 0) || (_fd_duty < 0) || (_fd_enable < 0) || (_fd_polarity < 0)) {
        int err = errno;
        cleanupFileDescriptors();
        throw std::runtime_error(std::string("PWM::constructor: failed to open one of pwm0/*: ") +
            std::strerror(err));
    }
}

PWM::~PWM() {
    if (_initialized) {
        // First disable PWM if it wasn’t already disabled:
        ::lseek(_fd_enable, 0, SEEK_SET);
        ::dprintf(_fd_enable, "0");

        // Then unexport “0” so the sysfs node goes away
        int fd_unexp = ::open(_unexportPath.c_str(), O_WRONLY);
        if (fd_unexp >= 0) {
            ::dprintf(fd_unexp, "0");
            ::close(fd_unexp);
        }
    }
    cleanupFileDescriptors();
}

void PWM::begin(int period_ns, const char* polarity) {
    if (_initialized) {
        // Already set up
        return;
    }
    // 1) Write the period (in nanoseconds):
    if (!writeInteger(_fd_period, period_ns)) {
        throw std::runtime_error("PWM::begin: failed to set period");
    }

    // 2) Write the polarity (“normal” or “inversed”):
    if (!writeString(_fd_polarity, polarity)) {
        throw std::runtime_error("PWM::begin: failed to set polarity");
    }

    // 3) Enable PWM (write “1”):
    if (!writeInteger(_fd_enable, 1)) {
        throw std::runtime_error("PWM::begin: failed to enable PWM");
    }
    _initialized = true;
}

void PWM::begin() {
    begin(DEFAULT_PERIOD_NS, NORMAL);
}

/// Sets a raw duty‐cycle in nanoseconds. Clamps to [MIN_DUTY_NS, MAX_DUTY_NS].
void PWM::setDutyCycleNs(int duty_ns) {
    if (!_initialized) {
        throw std::runtime_error("PWM::setDutyCycleNs called before begin()");
    }
    if (duty_ns < MIN_DUTY_NS) duty_ns = MIN_DUTY_NS;
    if (duty_ns > MAX_DUTY_NS) duty_ns = MAX_DUTY_NS;

    if (!writeInteger(_fd_duty, duty_ns)) {
        throw std::runtime_error("PWM::setDutyCycleNs: failed to write duty");
    }
}

/// 8‐bit analog write: maps [0..255] → [0..period_ns].
void PWM::analogWrite8bit(int value8) {
    if (!_initialized) {
        throw std::runtime_error("PWM::analogWrite8bit called before begin()");
    }
    if (value8 < 0)   value8 = 0;
    if (value8 > 255) value8 = 255;

    long long mapped = (static_cast<long long>(value8) * DEFAULT_PERIOD_NS) / 255;
    setDutyCycleNs(static_cast<int>(mapped));
}

/// Write a raw integer “value” directly to the duty‐cycle node.
void PWM::analogWrite(int rawValueNs) {
    if (!_initialized) {
        throw std::runtime_error("PWM::analogWrite called before begin()");
    }
    setDutyCycleNs(rawValueNs);
}

/// A simple digital on/off: 0 → 0 ns, otherwise → MAX (100%).
void PWM::digitalWrite(int level) {
    if (!_initialized) {
        throw std::runtime_error("PWM::digitalWrite called before begin()");
    }
    if (level == 0) {
        setDutyCycleNs(MIN_DUTY_NS);
    } else {
        setDutyCycleNs(MAX_DUTY_NS);
    }
}

/// Change polarity on‐the‐fly (e.g. “inversed”). Does *not* re‐enable.
void PWM::setPolarity(const char* polarity) {
    if (!_initialized) {
        throw std::runtime_error("PWM::setPolarity called before begin()");
    }
    if (!writeString(_fd_polarity, polarity)) {
        throw std::runtime_error("PWM::setPolarity: failed to write polarity");
    }
}

/// Change period on‐the‐fly (clamps to [MIN_PERIOD_NS, MAX_PERIOD_NS]).
/// *Warning:* If you change period after enabling, you may need to re‐write duty accordingly.
void PWM::setPeriod(int period_ns) {
    if (!_initialized) {
        throw std::runtime_error("PWM::setPeriod called before begin()");
    }
    if (period_ns < MIN_PERIOD_NS) period_ns = MIN_PERIOD_NS;
    if (period_ns > MAX_PERIOD_NS) period_ns = MAX_PERIOD_NS;

    if (!writeInteger(_fd_period, period_ns)) {
        throw std::runtime_error("PWM::setPeriod: failed to write period");
    }
}