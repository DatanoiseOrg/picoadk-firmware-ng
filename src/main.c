#include "pico/stdlib.h"
#include <stdio.h>

#define LED_DELAY_MS 500

int main() {
    // set gpio2 as output
    gpio_init(2);
      gpio_set_dir(2, GPIO_OUT);

    printf("Hello, World!\n");
    while(1) {
        gpio_put(2, 1);
        sleep_ms(LED_DELAY_MS);
    }
}