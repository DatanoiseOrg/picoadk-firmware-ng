#include <stdio.h>
#include <pico/stdlib.h>
#include <core.h>

#ifdef __cplusplus
extern "C" {
#endif

int main() {
    gpio_init(2);
    gpio_set_dir(2, GPIO_OUT);
    gpio_put(2, 1);

    int result = init_audio_i2s();
    if (result != 0) {
        printf("Failed to initialize audio subsystem\n");
        return -1;
    }
    

    while (true) {
       // __wfi();  // Wait for interrupt
        gpio_put(2,0);
        sleep_ms(100);
        gpio_put(2,1);
        sleep_ms(100);
    }
}

#ifdef __cplusplus
}
#endif
