#include <stdio.h>
#include <pico/stdlib.h>
#include <core.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(USE_AUDIO_I2S)
#include <audio_subsystem.h>
audio_buffer_pool_t *audiopool;
#endif

#define LED_DELAY_MS 500

int main() {
    #if defined(USE_AUDIO_I2S)
    audiopool = init_audio();
    #else
    #warn "Audio is not enabled"
    #endif

    // set gpio2 as output
    gpio_init(2);
    gpio_set_dir(2, GPIO_OUT);

    printf("Hello, World!\n");
    while (1) {
        gpio_put(2, 1);
        sleep_ms(LED_DELAY_MS);
    }
}

#ifdef __cplusplus
}
#endif
