#pragma once

#include <crc_check.h>
#include <serial.hpp>

namespace ld06_driver{
    class ld06_driver{
        private:
            const std::string port;
            uint8_t buf;
            uint32_t buf_len;
        public:

            //Parse scan data coming off the serial port
            int parse_scan();

            //Setup port and configure terminos
            bool init_port(std::string port);

            //CRC check function
            uint8_t CalCRC8(uint8_t *p, uint8_t len);
    };
}