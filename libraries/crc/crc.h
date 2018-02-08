#ifndef __CRC_H__
#define __CRC_H__
#include <stdint.h>

const static int32_t POLYNOMIAL   = 0x8408;
const static int32_t PRESET_VALUE = 0xFFFF;

int16_t crc16(uint8_t *data, uint16_t length);

#endif