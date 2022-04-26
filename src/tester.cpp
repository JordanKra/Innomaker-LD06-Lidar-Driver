//
// Created by jordank on 4/25/22.
//
#include "ld06_driver.hpp"
#include <iostream>
int main(int argc, char * argv[]){
    ld06_driver::ld06_driver driver;
    const char * port = "/dev/ttyUSB0";
    printf("Initializing connection to port\n");
    driver.init_connection(port);
    while(true){
        std::cout << "CRC: " << driver.parse_scan() << std::endl;
    }
}