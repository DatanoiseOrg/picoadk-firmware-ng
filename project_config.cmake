cmake_minimum_required(VERSION 3.12)
set(PROJECT_NAME picoadk-ng)

# if USB_MODE_PICOSDK is set to 1, the USB stack will be provided by the Pico SDK
# and no custom USB implementation will be used
set(USB_MODE_PICOSDK 1)

set(CPU_FREQ_KHZ 150000)