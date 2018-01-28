
#include <stdint.h>

const static int32_t POLYNOMIAL   = 0x8408;
const static int32_t PRESET_VALUE = 0xFFFF;

int16_t crc16(uint8_t *data, uint16_t length)
{
  int32_t current_crc_value = PRESET_VALUE;

  for (int i = 0; i < length; i++ ) {
    current_crc_value ^= data[i] & 0xFF;
    for (int j = 0; j < 8; j++) {
      if ((current_crc_value & 1) != 0) {
        current_crc_value = (current_crc_value >> 1) ^ POLYNOMIAL;
      } else {
        current_crc_value = current_crc_value >> 1;
      }
    }
  }
  current_crc_value = ~current_crc_value;

  return (int16_t)(current_crc_value & 0xFFFF);
}
