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

set(PICO_PLATFORM "rp2350-arm-s")

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
    src/main.cpp
)

# Add the standard library to the build
target_link_libraries(${PROJECT_NAME} pico_stdlib)

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
        hardware_sync_spin_lock
        hardware_sync
)

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
    target_include_directories(${PROJECT_NAME} PRIVATE core/lib/audio/include)
    target_sources(${PROJECT_NAME} PRIVATE src/audio_dsp.cpp)
endif()

if(ENABLE_FREERTOS)
    target_link_libraries(${PROJECT_NAME} FreeRTOS)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE
        CPU_FREQ_KHZ=${CPU_FREQ_KHZ}
        USE_AUDIO_I2S=${ENABLE_AUDIO_I2S}
        USB_MODE_PICOSDK=${USB_MODE_PICOSDK}

        PICO_USE_SW_SPIN_LOCKS=1

        CMAKE_PROJECT_NAME="${PROJECT_NAME}"

        GIT_COMMIT_HASH=\"${GIT_COMMIT_HASH}\"
        GIT_BRANCH=\"${GIT_BRANCH}\"
        GIT_TAG=\"${GIT_TAG}\"
)
pico_set_program_name(${PROJECT_NAME} "${PROJECT_NAME}")

target_link_options(${PROJECT_NAME} PRIVATE
        -Xlinker --print-memory-usage
)

if(USE_PSRAM)
    message(WARNING "Careful, using PSRAM support for RP2350. This is experimental and may not work as expected.")
	target_compile_definitions(${PROJECT_NAME} PRIVATE
        RP2350_CS_PIN=${RP2350_CS_PIN}
    )

    add_executable(${PROJECT_NAME}
        core/src/psram.cpp
    )

    target_include_directories(${PROJECT_NAME} PRIVATE core/include)

    add_custom_target(
        generate_linker_script ALL
        COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/tools/simplesub.py -i ${CMAKE_CURRENT_SOURCE_DIR}/core/ld/rp2350_psram.ld.in -o ${CMAKE_CURRENT_BINARY_DIR}/rp2350_psram.ld --sub __FLASH_LENGTH__ ${FLASH_LENGTH} --sub __EEPROM_START__ ${EEPROM_START} --sub __FS_START__ ${FS_START} --sub __FS_END__ ${FS_END} --sub __PSRAM_LENGTH__ ${PSRAM_LENGTH} --sub __RAM_LENGTH__ ${RAM_LENGTH}
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/core/ld/rp2350_psram.ld.in ${CMAKE_CURRENT_SOURCE_DIR}/tools/simplesub.py
    )

    add_dependencies(${PROJECT_NAME} generate_linker_script)

    pico_set_linker_script(${PROJECT_NAME} ${CMAKE_CURRENT_BINARY_DIR}/rp2350_psram.ld)
endif()

add_compile_options("-Wall" "-Wredundant-decls")

pico_add_extra_outputs(${PROJECT_NAME})

message(STATUS "Git commit hash: ${GIT_COMMIT_HASH}")
message(STATUS "Git branch: ${GIT_BRANCH}")
message(STATUS "Git tag: ${GIT_TAG}")
