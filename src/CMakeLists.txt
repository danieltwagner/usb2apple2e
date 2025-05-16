add_executable(usb2apple2e
    main.cpp
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(usb2apple2e pico_stdlib)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(usb2apple2e)

# Serial through USB
pico_enable_stdio_uart(usb2apple2e 0)
pico_enable_stdio_usb(usb2apple2e 1)
