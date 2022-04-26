#pragma once

#include <cstdint>
#define ANGLE_PER_FRAME 12
#define POINT_PER_PACK 12
#define HEADER 0x54
struct LidarPointStructDef
{
  uint16_t distance;
  uint8_t confidence;
};


struct ScanFrameDef{
    uint8_t header;
    uint8_t ver_len;
    uint16_t speed;
    uint16_t start_angle;
    LidarPointStructDef point[POINT_PER_PACK];
    uint16_t end_angle;
    uint16_t timestamp;
    uint8_t crc8;
};