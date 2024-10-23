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

int init_audio_i2s() {
    #if defined(USE_AUDIO_I2S)
    audiopool = init_audio();

    if (audiopool == NULL) {
        printf("Failed to initialize audio subsystem\n");
        return -1;
    }

    return 0;
    #else
    #warn "Audio is not enabled"
    #endif
}

void __not_in_flash_func(i2s_callback_func()) {
        audio_buffer_t *buffer = take_audio_buffer(audiopool, false);
        if (buffer == NULL) {
            return;
        }

        int32_t *samples = (int32_t *)buffer->buffer->bytes;

        // We are filling the buffer with 32-bit samples (2 channels)
        for (uint i = 0; i < buffer->max_sample_count; i++) {
            //float left_out, right_out = 0.0f;
            samples[i * 2 + 0] = 0; // float_to_int32(left_out);
            samples[i * 2 + 1] = 0; //float_to_int32(right_out);
        }

        buffer->sample_count = buffer->max_sample_count;
        give_audio_buffer(audiopool, buffer);
        return;
    }

#ifdef __cplusplus
}
#endif
