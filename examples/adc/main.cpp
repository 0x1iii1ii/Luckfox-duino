#include <iostream>
#include "adc.h"

ADC adc;

int main() {

    std::cout << "Hello and welcome to ADC example" << "!\n";
    std::cout << "Using both channel SARADC_IN0 and SARADC_IN1 "<< std::endl;
    std::cout << "ADC started!" << std::endl;
    while (1)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // debounce delay
        float scale = adc.readScale();
        if (scale < 0) {
            std::cerr << "Failed to read scale\n";
            break;
        }
        int raw0     = adc.readRaw(ADC::CH0);
        int raw1     = adc.readRaw(ADC::CH1);
        float volt0  = adc.readVoltage(ADC::CH0);
        float volt1  = adc.readVoltage(ADC::CH1);

        std::cout << "Scale (mV):     " << scale << "\n";
        std::cout << "CH0 raw:        " << raw0 << ", voltage: " << volt0 << " V\n";
        std::cout << "CH1 raw:        " << raw1 << ", voltage: " << volt1 << " V\n";
    }
    return 0;
}