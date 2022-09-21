cmake_minimum_required(VERSION 3.18)

include(pico_sdk_import.cmake)

project(picoadc)

add_executable( picoadc
    source.c
)

target_link_libraries(picoadc pico_stdlib hardware_adc)

pico_sdk_init()

pico_enable_stdio_usb(picoadc 1)
pico_enable_stdio_uart(picoadc 1)

pico_add_extra_outputs(picoadc)