cmake_minimum_required(VERSION 3.12)

set(PICO_SDK_FETCH_FROM_GIT on)
set(PICO_EXTRAS_FETCH_FROM_GIT on)

# Pull in SDK (must be before project)
include(cmake/pico_sdk_import.cmake)
include(cmake/pico_extras_import_optional.cmake)
include(cmake/freertos_import.cmake)
include(cmake/git_vars.cmake)

include(project_config.cmake)

project(${PROJECT_NAME} C CXX ASM)
# Export the project name to a file
file(WRITE "${CMAKE_BINARY_DIR}/project_name.txt" "${PROJECT_NAME}")

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "2.0.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 2.0.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

if (NOT DEFINED PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS)
    set(PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS 3000)
endif()

# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# if FREERTOS_INCLUDE_PATH is defined, use it
if (DEFINED FREERTOS_INCLUDE_PATH)
    target_include_directories(FreeRTOS PUBLIC ${FREERTOS_INCLUDE_PATH})
    echo ("Using FreeRTOS include path from parent scope ('${FREERTOS_INCLUDE_PATH}')")
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/core/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}
    ".")

add_executable(${PROJECT_NAME}
    src/main.c
)

# Add the standard library to the build
target_link_libraries(${PROJECT_NAME} pico_stdlib)


# Check if USB_MODE_PICOSDK is defined
if(NOT USB_MODE_PICOSDK)
    target_link_libraries(${PROJECT_NAME}
        tinyusb_device
        tinyusb_board
    )
endif()

if(ENABLE_AUDIO_I2S)
    add_subdirectory(core/lib/audio)
    target_link_libraries(${PROJECT_NAME} Audio)
endif()

if(ENABLE_FREERTOS)
    target_link_libraries(${PROJECT_NAME} FreeRTOS)
endif()

# Base libraries
target_link_libraries(${PROJECT_NAME}
        hardware_adc
        hardware_spi
        hardware_i2c
        hardware_dma
        hardware_pio
        hardware_interp
        hardware_timer
        hardware_watchdog
        hardware_clocks
        pico_unique_id
        pico_bootsel_via_double_reset
        pico_util_buffer
        pico_multicore
        pico_stdio_uart
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
        CPU_FREQ_KHZ=${CPU_FREQ_KHZ}
        USE_AUDIO_I2S=${ENABLE_AUDIO_I2S}
        USB_MODE_PICOSDK=${USB_MODE_PICOSDK}

        CMAKE_PROJECT_NAME="${PROJECT_NAME}"

        GIT_COMMIT_HASH=\"${GIT_COMMIT_HASH}\"
        GIT_BRANCH=\"${GIT_BRANCH}\"
        GIT_TAG=\"${GIT_TAG}\"
)

target_link_options(${PROJECT_NAME} PRIVATE
        -Xlinker --print-memory-usage
)

add_compile_options("-Wall" "-Wredundant-decls")

pico_add_extra_outputs(${PROJECT_NAME})

message(STATUS "Git commit hash: ${GIT_COMMIT_HASH}")
message(STATUS "Git branch: ${GIT_BRANCH}")
message(STATUS "Git tag: ${GIT_TAG}")
