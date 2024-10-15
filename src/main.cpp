#include <stdio.h>
#include <pico/stdlib.h>
#include <core.h>

#ifdef __cplusplus
extern "C" {
#endif

int main() {
    init_audio_i2s();;

    while (true) {
        __wfi();  // Wait for interrupt
    }
}

#ifdef __cplusplus
}
#endif
