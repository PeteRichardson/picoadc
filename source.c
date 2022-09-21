// Simple potentiometer adc demo program on RPi Pico
// 
#include <stdio.h>        // printf()
#include <stdlib.h>       // abs()
#include "pico/stdlib.h"  // stdio_init_all(), sleep_ms()
#include "hardware/adc.h" // adc_*()

#define MOVE_THRESHOLD 50
#define SCALED_MIN 0
#define SCALED_MAX 128

inline uint8_t scale(uint16_t raw) {
    return SCALED_MIN + raw * SCALED_MAX/4096;
}

int main() {
    stdio_init_all();
    
    adc_init();
    adc_gpio_init(26);      // GPIO26 is ADC0 on Pico and Pico W
    adc_select_input(0);

    uint16_t raw;           // = value direct from 12-bit adc
                            //    NOTE: HW may limit raw values e.g. joystick
                            //    that doesn't physically reach pot's max.
    uint16_t prevRaw;       // = previous adc value. Used to smooth output
    uint8_t scaled;         // = value after scaling to SCALED_MIN...SCALED_MAX

    while (true) {
        raw = adc_read();                     // Get a new 12 bit ADC val
        if (abs(raw - prevRaw) > MOVE_THRESHOLD) { // If it's a big enough move
            scaled =  scale(raw);                                  // ..scale
            printf("%4d->%3d:%*s\n", raw, scaled, scaled, "<->");  // ..and print
            prevRaw = raw;                  // NOTE: this must be inside the if.
        };
        sleep_ms(30);
    }
}