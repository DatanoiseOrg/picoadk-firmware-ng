#include <sysinit.h>

int sysinit() {
    #if defined(CPU_OVERCLOCK)
    #warning "CPU is overclocked"
    // Add more fine grained control over the overclocking
    vreg_set_voltage(VREG_VOLTAGE_1_30);
    int ret = set_sys_clock_khz(CPU_FREQ_KHZ, true);
    if (!ret) {
        return -1;
    }
    #else
    #warning "CPU is not overclocked"
    #endif
    return 0;
}