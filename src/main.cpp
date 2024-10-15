#include <stdio.h>
#include <pico/stdlib.h>
#include <core.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(USE_AUDIO_I2S)
#include <audio_dsp.h>
#endif

#define LED_DELAY_MS 500

int main() {
    init_audio_i2s();;

    while (true) {
        __wfi();  // Wait for interrupt
    }
}

#ifdef __cplusplus
}
#endif
