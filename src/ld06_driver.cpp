#include "ld06/ld06_driver.hpp"
#include "serial.hpp"
#include "scan.h"


namespace ld06_driver{

    int ld06_driver::parse_scan(){
        //Read in scans on the port and fill scan struct
        buf_len = serial::read(&buf);

    }
    
    bool ld06_driver::init_port(std::string port){
        //Connect to specified port
        int timeout = 5;
        while(!serial::connect(&port) && timeout > 0){
            //Attempt to reconnect
            if(timeout == 0){
                printf("Failed to connect to serial port after 5 attempts!")
                return false;
            }
            printf("Retrying...");
            timeout--;
        }
        //Configure port
        serial::configure();
        return true;
    }

    //CRC check function
    uint8_t ld06_driver::CalCRC8(uint8_t *p, uint8_t len){
        uint8_t crc = 0;
        for (uint16_t i = 0; i < len; i++){
            crc = CrcTable[(crc ^ *p++) & 0xff];
        }
        return crc;
    }
} //ld06_driver


