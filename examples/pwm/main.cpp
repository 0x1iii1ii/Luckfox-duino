#include <iostream>
#include "pwm.h"

#define PWM_RES 2

// * using luckfox-config to config PWM pin to enable, see pwm_def.h to see which pin is supported

PWM pwmLED(PWM0_M0);

int main() {
    // TIP Press <shortcut actionId="RenameElement"/> when your caret is at the
    // <b>lang</b> variable name to see how CLion can help you rename it.
    std::cout << "Hello and welcome to PWM example" << "!\n";
    std::cout << "PWM pin PWM0_M0" << std::endl;
    pwmLED.begin();
    int direction = PWM_RES; // 1 for increasing duty cycle, -1 for decreasing
    int value  = 0;
    while (1)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // debounce delay
        // Change PWM duty (0..255)
        value += direction;
        if (value >= 255) {
            value = 255;
            direction = -PWM_RES;
        }
        else if (value <= 0) {
            value = 0;
            direction = +PWM_RES;
        }
        // Write the 8-bit “analog” value
        pwmLED.analogWrite8bit(value);
        std::cout << "pwm value: " << value << "\n";
    }
    return 0;
}