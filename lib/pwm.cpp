//
// Created by 0x1iii1ii on 6/3/2025.
//

#include "pwm.h"

PWM::PWM(int pinNumber)
    : pin(pinNumber), initialized(false) {
    snprintf(pwm_path, sizeof(pwm_path), "/sys/class/pwm/pwmchip%d", pin);
    snprintf(pwm_duty, sizeof(pwm_duty), "/sys/class/pwm/pwmchip%d/pwm0/duty_cycle", pin);
    FILE *pwm_export = fopen(exportPath().c_str(), "w");
    if (!pwm_export) {
        perror("Failed to open PWM export");
    }
    fprintf(pwm_export, "0");
    fclose(pwm_export);
}

PWM::~PWM(void) {
    if (initialized) {
        FILE *pwm_unexport = fopen(unexportPath().c_str(), "w");
        if (!pwm_unexport) {
            perror("Failed to open PWM unexport");
        }
        fprintf(pwm_unexport, "0");
        fclose(pwm_unexport);
    }
}

std::string PWM::periodPath() const
{
    // "/sys/class/pwm/pwmchip<pin>/pwm0/period"
    return std::string(pwm_path) + "/pwm0/period";
}

std::string PWM::enablePath() const
{
    // "/sys/class/pwm/pwmchip<pin>/pwm0/enable"
    return std::string(pwm_path) + "/pwm0/enable";
}

std::string PWM::exportPath() const
{
    // "/sys/class/pwm/pwmchip<pin>/pwm0/export"
    return std::string(pwm_path) + "/export";
}
std::string PWM::unexportPath() const
{
    // "/sys/class/pwm/pwmchip<pin>/pwm0/unexport"
    return std::string(pwm_path) + "/unexport";
}
std::string PWM::polarityPath() const
{
    // "/sys/class/pwm/pwmchip<pin>/pwm0/polarity"
    return std::string(pwm_path) + "/pwm0/polarity";
}

bool PWM::setPeriod(unsigned int period) {
    FILE *period_file = fopen(periodPath().c_str(), "w");
    if (!period_file) {
        perror("Failed to open PWM period");
        return false;
    }
    fprintf(period_file, "%u", period);
    fclose(period_file);
    return true;
}

bool PWM::setEnable(bool enable) {
    FILE *enable_file = fopen(enablePath().c_str(), "w");
    if (!enable_file) {
        perror("Failed to open PWM enable");
        return false;
    }
    fprintf(enable_file, "%d", enable);
    fclose(enable_file);
    return true;
}

bool PWM::setPolarity(const char* polarity) {
    FILE *polarity_file = fopen(polarityPath().c_str(), "w");
    if (!polarity_file) {
        perror("Failed to open PWM polarity");
        return false;
    }
    fprintf(polarity_file, "%s", polarity);
    fclose(polarity_file);
    return true;
}

void PWM::begin(int period, const char* polarity) {
    if (initialized) {
        // Already set up
        return;
    }
    // 2) Write period (in ns)
    setPeriod(period);
    // 3) Set polarity to normal
    setPolarity(polarity);
    // 4) Enable PWM
    setEnable(true);
    initialized = true;
}

void PWM::begin(void) {
    if (initialized) {
        // Already set up
        return;
    }
    // 2) Write period (in ns)
    setPeriod(PERIOD_NS);
    // 3) Set polarity to normal
    setPolarity(NORMAL);
    // 4) Enable PWM
    setEnable(true);
    initialized = true;
}
void PWM::analogWrite8bit(int value)
{
    if (!initialized) {
        throw std::runtime_error("PWM::analogWrite called before begin()");
    }
    if (value < 0)   value = 0;
    if (value > MAX_8BIT) value = MAX_8BIT;

    // Map [0..255] → [0..PERIOD_NS]
    long long duty = (static_cast<long long>(value) * PERIOD_NS) / MAX_8BIT;
    setDutyCycleNs(static_cast<int>(duty));
}

void PWM::analogWrite(int value)
{
    if (!initialized) {
        throw std::runtime_error("PWM::analogWrite called before begin()");
    }
    setDutyCycleNs(value);
}

void PWM::digitalWrite(int level)
{
    if (!initialized) {
        throw std::runtime_error("PWM::digitalWrite called before begin()");
    }
    if (level == 0) {
        setDutyCycleNs(MIN_DUTY_NS);
    } else {
        setDutyCycleNs(MAX_DUTY_NS);
    }
}

void PWM::setDutyCycleNs(int duty_ns) {
    if (duty_ns < MIN_DUTY_NS) duty_ns = MIN_DUTY_NS;
    if (duty_ns > MAX_DUTY_NS) duty_ns = MAX_DUTY_NS;
    FILE *duty_cycle_file = fopen(pwm_duty, "w");
    if (!duty_cycle_file) {
        perror("Failed to open PWM duty cycle");
    }
    fprintf(duty_cycle_file, "%d", duty_ns);
    fclose(duty_cycle_file);
}