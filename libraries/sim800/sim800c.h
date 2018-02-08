#ifndef __SIM800C_H__
#define __SIM800C_H__

#include "Arduino.h"
#include <SoftwareSerial.h>

#define UART_DEBUG
#define DEBUG_BAUDRATE 9600
#define DEBUG_TX_PIN           8
#define DEBUG_RX_PIN           7

#ifdef UART_DEBUG
#define ERROR(x)            DSerial.println(x)
#define DEBUG(x)            DSerial.println(x);
#else
#define ERROR(x)
#define DEBUG(x)
#endif

#define DEFAULT_TIMEOUT     4

class SIM800C
{
  public:
    SIM800C(int baudRate) : DSerial(DEBUG_TX_PIN, DEBUG_RX_PIN) {
      Serial.begin(baudRate);
      DSerial.begin(DEBUG_BAUDRATE);
    };

    // 检查缓存数
    int checkReadable(void);

    // 读取字节到buffer
    int readBuffer(char* buffer,int count, unsigned int timeOut = DEFAULT_TIMEOUT);
    
    // 清除buffer数组
    void cleanBuffer(char* buffer, int count);

    // 功能: 发送字符串指令 cmd
    void sendCmd(const char* cmd);

    // 功能: 等待timeout时间, 读取缓存判断resp是否存在其中
    // 返回值: 0: 存在; 其他: 不存在
    int waitForResp(const char* resp, unsigned timeout);

    // 功能: 发送cmd指令以后, 等待timeout时间, 读取缓存判断resp是否存在其中
    // 返回值: 0: 成功; 其他: 失败
    int sendCmdAndWaitForResp(const char* cmd, const char *resp, unsigned timeout);

    // 功能: 发送 AT
    // 返回值: 0: 成功; 其他: 失败
    int sendAT(void);

    // 功能: 发送 '+++'
    // 返回值: 0: 成功; 其他: 失败
    int sendPlusMark(void);

    SoftwareSerial DSerial;

  private:
};
#endif
