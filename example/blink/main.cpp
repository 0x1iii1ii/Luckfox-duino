#include <iostream>
#include "gpio.h"

#define LED_USER_PIN GPIO1_A2 //34
#define BOOT_BUTTON_PIN GPIO4_C0 //144
GPIO LED(LED_USER_PIN);
GPIO BTN_BOOT(BOOT_BUTTON_PIN);
bool state = false;

int main() {
    std::cout << "Hello and welcome to LED Blink example" << "!\n";
    std::cout << "LED pin " << LED_USER_PIN << std::endl;
    std::cout << "BUTTON pin " << BOOT_BUTTON_PIN << std::endl;
    LED.pinMode(OUTPUT); // set as output
    BTN_BOOT.pinMode(INPUT); // set as input
    std::chrono::steady_clock::time_point lastToggleTime = std::chrono::steady_clock::now();
    auto loopc = 0;
    while (loopc < 20)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // debounce delay

        //* Toggle 1 */

        // static bool toggle = false;
        // auto btn_state = BTN_BOOT.digitalRead();
        // if (btn_state == LOW && !toggle) {
        //     toggle = true;
        //     loopc++;
        //     LED.digitalWrite(HIGH);
        //     std::cout << "LED is " << (LED.digitalRead() ? "on" : "off") << std::endl;
        // } else if (btn_state == HIGH && toggle) {
        //     LED.digitalWrite(LOW);
        //     std::cout << "LED is " << (LED.digitalRead() ? "on" : "off") << std::endl;
        //     toggle = false;
        // }

        //* Toggle 2 */

        static bool lastState = HIGH;
        if (BTN_BOOT.digitalRead() == LOW && lastState == HIGH) {
            LED.digitalWrite(!LED.digitalRead());
            loopc++;
            std::cout << "LED is " << (LED.digitalRead() ? "on" : "off") << std::endl;
        }
        lastState = BTN_BOOT.digitalRead();

        //* Blink */

        // auto now = std::chrono::steady_clock::now();
        // if (now - lastToggleTime >= std::chrono::milliseconds(500)) {
        //     loopc++;
        //     state = !state;
        //     state ? LED.digitalWrite(HIGH) : LED.digitalWrite(LOW);
        //     std::cout << "LED is " << (LED.digitalRead() ? "on" : "off") << std::endl;
        //     lastToggleTime = now;
        // }
    }
    return 0;
}