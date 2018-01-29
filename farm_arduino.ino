#include <SHT1x.h>
#include <stdint.h>
#include "crc16.h"
#include "struct.h"
#include "sh1x.h"
#include "temp.h"
#include "humi.h"
#include "register.h"
#include "keepAlive.h"
#include "handData.h"
#include "avr/boot.h"

void setup() {
  Serial.begin(38400);
}
void loop() {
  if (Serial) {
    int d_len = Serial.available();
    if ( d_len > 0)
    {
      uint8_t data[d_len];
      for (int i = 0; i < d_len; i++)
        data[i] = Serial.read();
        handData(data, d_len);
    }
  }

  // 采集数据
  if (registe_flag == -1 ) {
    sendRegister();
  } else {
    if (times % interval == 0) {
      sendTemp();
      sendHumi();
    }
  }
  handSequence();
  times++;
  delay(1000);
}



