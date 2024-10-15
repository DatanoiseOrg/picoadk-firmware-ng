cmake_minimum_required(VERSION 3.12)
set(PROJECT_NAME picoadk-ng)

# if USB_MODE_PICOSDK is set to 1, the USB stack will be provided by the Pico SDK
# and no custom USB implementation will be used
set(USB_MODE_PICOSDK 1)

# CPU Related settings
set(CPU_FREQ_KHZ 150000)

# Audio settings
set(AUDIO_SAMPLE_RATE 48000)
set(AUDIO_SAMPLE_BITS 32)

# Features to enable
set(ENABLE_AUDIO_I2S 1)

# Board specific I/O settings
set(PIN_I2S_DOUT 16)
set(PIN_I2S_BCK 17)