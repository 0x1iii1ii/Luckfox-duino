#include <iostream>
#include "ssd1306.h"

char msg[] = "Hi Luckfox!";

int main() {

    std::cout << "Hello and welcome to OLED I2C example" << "!\n";
    if (ssd1306_init()) {
        std::cerr << "no oled attached to /dev/i2c-3" << std::endl;
        return 1;
    }
    std::cout << "OLED started!" << std::endl;
    ssd1306_oled_default_config(32, 128);
    ssd1306_oled_clear_screen();
    ssd1306_oled_set_XY(30,0);
    ssd1306_oled_write_string(0, msg);
    // ssd1306_oled_scroll_onoff(1);
    std::cout << "OLED ended!" << std::endl;
    return 0;
}