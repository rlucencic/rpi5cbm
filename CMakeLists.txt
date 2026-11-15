# rpi5cbm: the Commodore 64 and 128 on the Raspberry Pi 5.
#
#   cmake -S . -B build -G Ninja && cmake --build build
#   build/rpi5cbm --help
#
# The Commodore itself is esp32cbm's (../esp32cbm/components/cbm, platform
# independent), the runtime rpi5emu's (../rpi5emu), the 6502 and the Z80
# (the C128's) esp32emu's (../esp32emu): all four cloned side by side.
cmake_minimum_required(VERSION 3.20)
project(rpi5cbm C)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "" FORCE)
endif()

set(ESP32CBM_DIR "${CMAKE_CURRENT_LIST_DIR}/../esp32cbm" CACHE PATH "esp32cbm checkout: the Commodore")
if(NOT EXISTS "${ESP32CBM_DIR}/components/cbm/include/cbm.h")
    message(FATAL_ERROR "No esp32cbm at ${ESP32CBM_DIR}: clone github.com/rlucencic/esp32cbm beside rpi5cbm")
endif()

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../rpi5emu" rpi5emu)

file(GLOB CBM_SOURCES "${ESP32CBM_DIR}/components/cbm/*.c")
add_executable(rpi5cbm
    src/main.c
    src/settings.c
    src/rom_store.c
    ${CBM_SOURCES})
target_include_directories(rpi5cbm PRIVATE
    src
    "${ESP32CBM_DIR}/components/cbm/include"
    "${ESP32CBM_DIR}/components/cbm")
# The C128's Z80 in T-states, reads of unmapped banks through the MMU, as esp32cbm's
target_compile_definitions(rpi5cbm PRIVATE CONFIG_Z80_TIMING_TSTATES=1 CONFIG_Z80_READ_SPECIAL=1)
rpi5emu_add_cores(rpi5cbm m6502 z80 diskspace)
target_link_libraries(rpi5cbm PRIVATE rpi5emu)
target_compile_options(rpi5cbm PRIVATE -Wall -Wextra -Wno-unused-parameter)

install(TARGETS rpi5cbm)
