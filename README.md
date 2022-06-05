# SNDWAY_SW525B_USB
Read [dB] via libusb1.0  
Digital Sound Level Meter SNDWAY SW-525B 

https://www.amazon.co.jp/dp/B07JZG2MXL

https://www.banggood.com/SNDWAY-SW-525B-Digital-Sound-Level-Meter-Noise-Decibel-Meter-30~130dB-Large-Display-p-1216339.html

# Environment
- libusb https://github.com/libusb/libusb
- C++11

# FAQ
## I can't configure cmake
If you use Windows,please use [msys](https://www.msys2.org/) and setup MinGW environment.
and `pacman -S mingw-w64-x86_64-libusb` .

or, simply you can make empty project with MSVC,and add set include,lib for libusb,copy main.cpp

