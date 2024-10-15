#include <stdio.h>
#include <pico/stdlib.h>
#include <core.h>

#ifdef __cplusplus
extern "C" {
#endif

int main() {
    int result = init_audio_i2s();
    if (result != 0) {
        printf("Failed to initialize audio subsystem\n");
        return -1;
    }

    while (true) {
        __wfi();  // Wait for interrupt
    }
}

#ifdef __cplusplus
}
#endif
