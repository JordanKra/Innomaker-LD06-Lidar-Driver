#include "LD06/serial.hpp"
#include <iostream>

namespace serial{
            //Connect to a serial port
            bool serial::connect(const char *port){
                std::cout << "Attempting to connect to port: " << port << std::endl;
                port_number = open(port, O_RDWR);
                if(port_number < 0){
                    printf("Error %i connecting to the serial port!\n", errno);
                    return false;
                }
                printf("Connected to serial port!\n");
                return true;
            }

            //Configure a serial port
            void serial::configure(){
                //Get params from port
                if(tcgetattr(port_number, &tty) != 0){
                    printf("Error %i from tcgetattr\n", errno);
                    return;
                }
                //Set port parameters
                tty.c_cflag &= ~PARENB;
                tty.c_cflag &= ~CSTOPB;
                tty.c_cflag |= CS8; // 8 bits per byte (most common)
                tty.c_cflag &= ~CRTSCTS;
                tty.c_cflag |= CREAD | CLOCAL;
                tty.c_lflag &= ~ICANON;
                tty.c_lflag &= ~ECHO; // Disable echo
                tty.c_lflag &= ~ECHOE; // Disable erasure
                tty.c_lflag &= ~ECHONL; // Disable new-line echo
                tty.c_lflag &= ~ISIG;
                tty.c_iflag &= ~(IXON | IXOFF | IXANY);
                tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);
                tty.c_oflag &= ~ONLCR;
                tty.c_oflag &= ~OPOST;

                //Set baud rate, we only read from the lidar so only input speed needed
                cfsetispeed(&tty, B230400);

                if (tcsetattr(port_number, TCSANOW, &tty) != 0) {
                    printf("Error %i from tcsetattr\n", errno);
                }
            }

            //Read data from the serial port return is number of bytes read
            uint32_t serial::read_scan(char *buf, int length){
                uint32_t len = read(port_number, buf, length);
                if(len < 0){
                    printf("Read error!\n");
                    return -1;
                }
                return len;
            }

}//serial