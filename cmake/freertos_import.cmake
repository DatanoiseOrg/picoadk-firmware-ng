cmake_minimum_required(VERSION 3.12)

include(project_config.cmake)
set(FREERTOS_SRC_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/core/lib/FreeRTOS-Kernel")

add_library(FreeRTOS STATIC
    ${FREERTOS_SRC_DIRECTORY}/event_groups.c
    ${FREERTOS_SRC_DIRECTORY}/list.c
    ${FREERTOS_SRC_DIRECTORY}/queue.c
    ${FREERTOS_SRC_DIRECTORY}/stream_buffer.c
    ${FREERTOS_SRC_DIRECTORY}/tasks.c
    ${FREERTOS_SRC_DIRECTORY}/timers.c
    ${FREERTOS_SRC_DIRECTORY}/portable/MemMang/heap_3.c
    ${FREERTOS_SRC_DIRECTORY}/portable/GCC/ARM_CM0/port.c
)

target_include_directories(FreeRTOS PUBLIC
    ${FREERTOS_CFG_DIRECTORY}/
    ${FREERTOS_SRC_DIRECTORY}/include
    ${FREERTOS_SRC_DIRECTORY}/portable/GCC/ARM_CM0
)

math(EXPR CPU_CLOCK_HZ "${CPU_FREQ_KHZ} * 1000")
target_compile_definitions(FreeRTOS PUBLIC -DconfigCPU_CLOCK_HZ=${CPU_CLOCK_HZ})

# Export FreeRTOS include path to parent scope
set(FREERTOS_INCLUDE_PATH ${FREERTOS_SRC_DIRECTORY}/include PARENT_SCOPE)
