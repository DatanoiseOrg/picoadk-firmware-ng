cmake_minimum_required(VERSION 3.12)

include(${CMAKE_CURRENT_SOURCE_DIR}/../../../project_config.cmake)

add_library(Audio STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/src/audio.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/audio_i2s.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/audio_subsystem.c
)

target_include_directories(Audio PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(Audio PUBLIC
	AUDIO_SAMPLE_RATE=${AUDIO_SAMPLE_RATE}
	PIN_I2S_DOUT=${PIN_I2S_DOUT}
	PIN_I2S_BCK=${PIN_I2S_BCK}
)

pico_generate_pio_header(Audio ${CMAKE_CURRENT_LIST_DIR}/piosrc/audio_i2s.pio)

target_link_libraries(Audio pico_stdlib pico_util_buffer pico_multicore hardware_pio hardware_dma)
