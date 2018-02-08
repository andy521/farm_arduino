#include <gprs.h>
#include <sim800c.h>
#include <SHT1x.h>
#include <SoftwareSerial.h>
#include <stdint.h>
#include <gprs.h>
#include <crc.h>

#include "struct.h"
#include "sh1x.h"
#include "temp.h"
#include "sim800.h"
#include "humi.h"
#include "register.h"
#include "keepAlive.h"
#include "handData.h"
#include "avr/boot.h"


void setup() {
  // 串口输出
  Serial.begin(9600);
  // 等待串口被打开
  while (!Serial);
  gprsInit();
}

void loop() {
  int d_len = Serial.available();
  if ( d_len > 0)
  {
    uint8_t data[d_len];
    for (int i = 0; i < d_len; i++){
      data[i] = Serial.read();
      gprs.DSerial.write(data[i]);
    }
    handData(data, d_len);
  }
  
  if (times % interval == 0) {
    if (registe_flag == -1 ) {
      sendRegister();
    } else {
      sendTemp();
      sendHumi();
    }
  }
  handSequence();
  times++;
  delay(1000);
}



