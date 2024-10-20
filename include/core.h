#pragma once

#include <dsp_helper.h>
#include <pico/stdlib.h>
#include <hardware/adc.h>
#include <hardware/spi.h>
#include <hardware/i2c.h>
#include <hardware/dma.h>
#include <hardware/pio.h>
#include <hardware/interp.h>
#include <hardware/timer.h>
#include <hardware/watchdog.h>
#include <hardware/clocks.h>
#include <hardware/vreg.h>
#include <hardware/structs/rosc.h>
#include <hardware/sync.h>

#if defined(USE_AUDIO_I2S)
#include <audio_dsp.h>
#endif

#include <sysinit.h>