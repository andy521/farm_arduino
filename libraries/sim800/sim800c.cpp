#include "sim800c.h"

int SIM800C::checkReadable(void)
{
  return Serial.available();
}

int SIM800C::readBuffer(char *buffer, int count, unsigned int timeOut)
{
  int i = 0;
  unsigned long timerStart, timerEnd;
  timerStart = millis();
  while (1) {
    while (Serial.available()) {
      char c = Serial.read();
      if (c == '\r' || c == '\n') c = '$';
      buffer[i++] = c;
      if (i > count - 1)break;
    }
    if (i > count - 1)break;
    timerEnd = millis();
    if (timerEnd - timerStart > 1000 * timeOut) {
      break;
    }
  }
  delay(500);
  while (Serial.available()) {  // display the other thing..
    Serial.read();
  }
  return 0;
}

void SIM800C::cleanBuffer(char *buffer, int count)
{
  for (int i = 0; i < count; i++) {
    buffer[i] = '\0';
  }
}

void SIM800C::sendCmd(const char* cmd)
{
  Serial.write(cmd);
}

int SIM800C::waitForResp(const char *resp, unsigned int timeout)
{
  int len = strlen(resp);
  int sum = 0;
  unsigned long timerStart, timerEnd;
  timerStart = millis();

  while (1) {
    if (Serial.available()) {
      char c = Serial.read();
      sum = (c == resp[sum]) ? sum + 1 : 0;
      if (sum == len)
        break;
    }
    timerEnd = millis();
    if (timerEnd - timerStart > 1000 * timeout) {
      return -1;
    }
  }

  while (Serial.available()) {
    Serial.read();
  }

  return 0;
}

int SIM800C::sendCmdAndWaitForResp(const char* cmd, const char *resp, unsigned timeout)
{
  sendCmd(cmd);
  return waitForResp(resp, timeout);
}

int SIM800C::sendAT(void)
{
  int ret = sendCmdAndWaitForResp("AT\r\n", "OK", DEFAULT_TIMEOUT);
  return ret;
}

int SIM800C::sendPlusMark(void)
{
  int ret = sendCmdAndWaitForResp("+++", "OK", DEFAULT_TIMEOUT * 2);
  return ret;
}
