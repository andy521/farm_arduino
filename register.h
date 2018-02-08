#include "avr/boot.h"

f_f0 ff0; // 以后永久存储
int registe_flag = -1;

// 发送注册
void sendRegister() {
  f_head head;
  f_00 f00;
  int16_t crc;

  int b_length = sizeof(f_00); // 消息体长度

  int16_t d_length = b_length + sizeof(f_head) + sizeof(int16_t);  // 数据包总长度
  char * data =  (char *)malloc(d_length);
  int d_position = 0; //指针赋值标签

  // 消息体头部
  head.length = b_length;
  head.sequence = sequence++;
  head.type = 0;
  memcpy(data + d_position, &head, sizeof(f_head));
  d_position += sizeof(f_head);

  // 消息体内容
  f00.model = 0;
  for (int i = 0; i < 10; i++)
  {
    f00.macAddress[i] = boot_signature_byte_get(i + 14);
  }
  memcpy(data + d_position, &f00, b_length);
  d_position += b_length;

  // 消息体的校验
  uint8_t tobyte[b_length];
  memcpy(tobyte, &f00, b_length);
  crc = crc16(tobyte, b_length);
  memcpy(data + d_position, &crc, b_length);

  // 发送
  uint8_t d_tobyte[d_length];
  memcpy(d_tobyte, data, d_length);
  Serial.write(d_tobyte, d_length);
}

