#include "LD06/serial.hpp"
#include "LD06/crc_check.h"

namespace serial{

    class serial{
            //Connect to a serial port
            bool serial::connect(std::string *port){
                port_number = open(port, O_RDWR);
                if(port_number < 0){
                    printf("Error connecting to the serial port!");
                    return false;
                }
                return true;
            }

            //Configure a serial port
            void serial::configure(){

                //Get params from port
                if(tcgetattr(port_number, &tty) != 0){
                    printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
                    return 1;
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
                    printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
                }
            }

            //Read data from the serial port return is number of bytes read
            uint32_t serial::read(uint8_t *buf){
                uint32_t len = read(port_number, &buf, sizeof(buf));
                if(len < 0){
                    printf("Read error: %s", strerror(errno));
                    return -1;
                }
                return len;
            }

    };

} //serial