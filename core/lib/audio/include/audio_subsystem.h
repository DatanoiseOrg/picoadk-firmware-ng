#ifndef __AUDIO_SUBSYSTEM_H__
#define __AUDIO_SUBSYSTEM_H__


#ifdef __cplusplus
extern "C" {
#endif


#define SAMPLES_PER_BUFFER 64 // Samples / channel

#define USE_AUDIO_I2S 1
#include "audio_i2s.h"
#include <stdio.h>

audio_buffer_pool_t *init_audio();

#ifdef __cplusplus
}
#endif


#endif // __AUDIO_SUBSYSTEM_H__