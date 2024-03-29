#pragma once

#include <crc_check.h>
#include "scan.h"
#include <string>
#include "serial.hpp"

namespace ld06_driver{
    class ld06_driver{
        private:
            const std::string port;
            uint32_t buf_len;
            struct ScanFrameDef *scan;
            struct LidarPointStructDef point;
            serial::serial serial_port;
            char buf[];
        public:

            //Parse scan data coming off the serial port
            int parse_scan();

            //Setup port and configure terminos
            bool init_connection(const char * port);

            //CRC check function
            uint8_t CalCRC8(char *p, uint8_t len);
    };
}