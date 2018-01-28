// 处理接收到的指令
void handData(uint8_t *data, int len)
{
  f_head head;
  int h_len = sizeof(f_head);
  memcpy(&head, data, h_len);

  switch (head.type) {
    case 0xF0:
      handlerRegister(data + h_len);
      break;
    case 0x01:
      handlerKeepAlive();
      break;
    default:
      break;

  }
}



