#pragma once

#include <fcntl.h> // Contains file controls like O_RDWR
#include <cerrno> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include <string>
#include <cstdint>

namespace serial{
    class serial{
        private:
            struct termios tty;
            int port_number;
        public:
            //Connect to a serial port
            bool connect(const char *port);

            //Configure a serial port
            void configure();

            //Read data from the serial port
            uint32_t read_scan(uint8_t *buf);

    };
}