#include <cstring>
#include "LD06/ld06_driver.hpp"
#include "LD06/serial.hpp"
#include "LD06/scan.h"


namespace ld06_driver{

    int ld06_driver::parse_scan(){
        //Read in scans on the port and fill scan struct
        buf_len = serial_port.read_scan(buf, sizeof(scan));
        //calculate CRC
        //scan.crc8 = CalCRC8(buf, buf_len);
        //parse the rest of the data
        //scan = (ScanFrameDef *)buf;
        printf("Read %i bytes off the serial port\n", buf_len);
        //return scan.crc8;
    }

    //Connect to and configure the specified serial port
    bool ld06_driver::init_connection(const char *port){
        //Connect to specified port
        printf("Attempting to connect to the port\n");
        int timeout = 5;
        while(!serial_port.connect(port)){
            //Attempt to reconnect
            if(timeout == 0){
                printf("Failed to connect to serial port after 5 attempts!");
                return false;
            }
            printf("Retrying...\n");
            timeout--;
        }
        //Configure port
        serial_port.configure();
        return true;
    }

    //CRC check function
    uint8_t ld06_driver::CalCRC8(char *p, uint8_t len){
        uint8_t crc = 0;
        for (uint16_t i = 0; i < len; i++){
            crc = CrcTable[(crc ^ *p++) & 0xff];
        }
        return crc;
    }
} //ld06_driver


