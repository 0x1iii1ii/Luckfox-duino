#include <iostream>
#include "gpio.h"
#include "pwm.h"
#include "uart.h"

#define LED_USER_PIN GPIO1_A2 //34
#define BOOT_BUTTON_PIN GPIO4_C0 //144
#define PWM_RES 2
GPIO LED(LED_USER_PIN);
GPIO BTN_BOOT(BOOT_BUTTON_PIN);
bool state = false;
PWM pwmLED(PWM0_M0);
UART testSerial("/dev/ttyS3", B115200);


void serialRead(const std::string &rawdata)
{
    std::cout << "\nSerial Received: " << rawdata << std::endl;
}

int main() {

    std::cout << "Hello and welcome to LED Blink example" << "!\n";
    std::cout << "LED pin " << LED_USER_PIN << std::endl;
    std::cout << "BUTTON pin " << BOOT_BUTTON_PIN << std::endl;
    if (!testSerial.isOpen()) {
        std::cerr << "Failed to open serial port /dev/ttyS3" << std::endl;
        return 1;
    }
    std::cout << "Serial port started!" << std::endl;
    testSerial.writeSerial("hi from luckfox serial!\r\n");
    testSerial.setDataReceivedCallback(serialRead);
    // Start background reading
    testSerial.startReading();
    LED.pinMode(OUTPUT); // set as output
    BTN_BOOT.pinMode(INPUT); // set as input
    pwmLED.begin();
    std::chrono::steady_clock::time_point lastToggleTime = std::chrono::steady_clock::now();
    int direction = PWM_RES; // 1 for increasing duty cycle, -1 for decreasing
    int value  = 0;
    std::string userInput;
    while (1)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // debounce delay
        std::cout << "Enter message (type 'q' to quit): ";
        std::getline(std::cin, userInput);
        if (userInput == "q") {
            break;
        }
        testSerial.writeSerial(userInput + "\r\n");
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

        // static bool lastState = HIGH;
        // if (BTN_BOOT.digitalRead() == LOW && lastState == HIGH) {
        //     LED.digitalWrite(!LED.digitalRead());
        //     loopc++;
        //     std::cout << "LED is " << (LED.digitalRead() ? "on" : "off") << std::endl;
        // }
        // lastState = BTN_BOOT.digitalRead();

        //* Blink */

        // auto now = std::chrono::steady_clock::now();
        // if (now - lastToggleTime >= std::chrono::milliseconds(500)) {
        //     loopc++;
        //     state = !state;
        //     state ? LED.digitalWrite(HIGH) : LED.digitalWrite(LOW);
        //     std::cout << "LED is " << (LED.digitalRead() ? "on" : "off") << std::endl;
        //     lastToggleTime = now;
        // }

        //* PWM */

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
    testSerial.stopReading();
    return 0;
}