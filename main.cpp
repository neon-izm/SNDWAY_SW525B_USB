#include <iostream>
#include <thread>
#include <chrono>
#include <libusb.h>

#define VID 0x0483 // for SNDWAY
#define PID 0x5750 // SW-525B
#define INTF_NUM 0
#define RECEIVE_ADDRESS 0x81 // receive
#define SEND_ADDRESS 0x01 // send
#define MAX_PACKET_SIZE 64 // packet_length

int main() {
    uint8_t receiveBuffer[MAX_PACKET_SIZE];
    uint8_t sendBuffer[MAX_PACKET_SIZE];

    int receiveLength;
    int r;

    r = libusb_init(nullptr);
    if (r < 0) {
        printf("libusb_init() failed: %s\n", libusb_error_name(r));
        return -1;
    }

    libusb_device_handle *handle = libusb_open_device_with_vid_pid(nullptr, VID, PID);
    if (handle == nullptr) {
        printf("libusb_open_device_with_vid_pid() failed: %s\n", libusb_error_name(r));
        libusb_exit(nullptr);
        return -1;
    }

    r = libusb_claim_interface(handle, INTF_NUM);
    if (r != 0) {
        printf("libusb_claim_interface() failed: %s\n", libusb_error_name(r));
        libusb_close(handle);
        return -1;
    }
    printf("loop start (Ctrl+C to exit)\n");
    float volumeDb=0;
    while (true) {
        int sendLength = 1;
        sendBuffer[0] = 0xb3;
        libusb_interrupt_transfer(handle, SEND_ADDRESS, sendBuffer, sizeof(sendBuffer), &sendLength, 100);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        r = libusb_interrupt_transfer(handle, RECEIVE_ADDRESS, receiveBuffer, sizeof(receiveBuffer), &receiveLength, 100);
        switch (r) {
            case 0:
                /*for (int i = 0; i < receiveLength; i++)
                    printf("%02x ", receiveBuffer[i]);
                printf("\n");*/
                volumeDb= ((int)receiveBuffer[0] * 255 + (int)receiveBuffer[1]) * 0.1;
                printf("volume:%lf \n",volumeDb);
                break;
            case LIBUSB_ERROR_TIMEOUT:
                break;
            default:
                printf("libusb_interrupt_transfer() failed: %s\n", libusb_error_name(r));
                goto release;
                break;
        }

    }
    release:
    libusb_release_interface(handle, INTF_NUM);
    libusb_close(handle);
    libusb_exit(nullptr);

    return 0;
}
