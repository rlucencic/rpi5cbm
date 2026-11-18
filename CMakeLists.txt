# sdlcbm: the Commodore 64 and 128 with SDL 3.
#
#   cmake -S . -B build -G Ninja && cmake --build build
#   build/sdlcbm --help
#
# The Commodore itself is esp32cbm's (../esp32cbm/components/cbm, platform
# independent), the runtime sdlemu's (../sdlemu), the 6502 and the Z80
# (the C128's) esp32emu's (../esp32emu): all four cloned side by side.
cmake_minimum_required(VERSION 3.20)
project(sdlcbm C)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "" FORCE)
endif()

set(ESP32CBM_DIR "${CMAKE_CURRENT_LIST_DIR}/../esp32cbm" CACHE PATH "esp32cbm checkout: the Commodore")
if(NOT EXISTS "${ESP32CBM_DIR}/components/cbm/include/cbm.h")
    message(FATAL_ERROR "No esp32cbm at ${ESP32CBM_DIR}: clone github.com/rlucencic/esp32cbm beside sdlcbm")
endif()

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../sdlemu" sdlemu)

file(GLOB CBM_SOURCES "${ESP32CBM_DIR}/components/cbm/*.c")
add_executable(sdlcbm
    src/main.c
    src/settings.c
    src/rom_store.c
    ${CBM_SOURCES})
target_include_directories(sdlcbm PRIVATE
    src
    "${ESP32CBM_DIR}/components/cbm/include"
    "${ESP32CBM_DIR}/components/cbm")
# The C128's Z80 in T-states, reads of unmapped banks through the MMU, as esp32cbm's
target_compile_definitions(sdlcbm PRIVATE CONFIG_Z80_TIMING_TSTATES=1 CONFIG_Z80_READ_SPECIAL=1)
sdlemu_add_cores(sdlcbm m6502 z80 diskspace)
target_link_libraries(sdlcbm PRIVATE sdlemu)
target_compile_options(sdlcbm PRIVATE -Wall -Wextra -Wno-unused-parameter)

install(TARGETS sdlcbm)
