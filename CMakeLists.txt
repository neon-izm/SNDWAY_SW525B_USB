cmake_minimum_required(VERSION 3.5)
project(sndway-usb)

find_package(PkgConfig REQUIRED)
pkg_check_modules(libusb-1.0 REQUIRED libusb-1.0)

add_executable(sndway-usb
    main.cpp
)

set_property(TARGET sndway-usb PROPERTY CXX_STANDARD 11)

target_compile_options(sndway-usb
    PRIVATE ${libusb-1.0_CFLAGS}
)

target_link_libraries(sndway-usb
    ${libusb-1.0_LIBRARIES}
)
