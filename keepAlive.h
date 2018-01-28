
// 心跳包
void sendKeepAlive() {
  f_head head;
  int16_t crc;
  
  int d_position = 0; //指针赋值标签
  int16_t d_length = sizeof(f_head) + sizeof(int16_t);  // 数据包总长度
  char * data =  (char *)malloc(d_length);
  
  // 消息体头部
  head.length = 0;
  head.sequence = count;
  head.type = 1;
  memcpy(data + d_position, &head, sizeof(f_head));
  d_position += sizeof(f_head);

  // 消息体的校验
  crc = 0;
  memcpy(data + d_position, &crc, 2);

  // 发送
  uint8_t d_tobyte[d_length];
  memcpy(d_tobyte, data, d_length);
  Serial.write(d_tobyte, d_length);
}


void handlerKeepAlive() {
  sendKeepAlive();
}





