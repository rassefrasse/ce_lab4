cmake_minimum_required(VERSION 3.13)
set(PICO_BOARD pico)
include(pico_sdk_import.cmake)

project(task1 C CXX ASM)
set(CMAKE_C_STANDARD 11)
pico_sdk_init()

add_executable(task1
    test.c
)

target_link_libraries(task1 pico_stdlib)

# printf goes over USB serial (/dev/ttyACM0), not the UART pins
pico_enable_stdio_usb(task1 1)
pico_enable_stdio_uart(task1 0)

# generates .uf2, .bin, .hex and a .dis disassembly
pico_add_extra_outputs(task1)
