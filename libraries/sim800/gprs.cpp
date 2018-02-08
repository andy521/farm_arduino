
#include <stdio.h>
#include "gprs.h"

int GPRS::init(void)
{

#if 0
  for (int i = 0; i < 2; i++) {
    sendCmd("AT\r\n");
    delay(100);
  }
  sendCmd("AT+CFUN=1\r\n");
  if (0 != checkSIMStatus()) {
    ERROR("ERROR:checkSIMStatus");
    return -1;
  }

#endif
  if (sendCmdAndWaitForResp("AT\r\n", "OK\r\n", DEFAULT_TIMEOUT * 3)) {
    return -1;
  }
  if (sendCmdAndWaitForResp("AT+CFUN=1\r\n", "OK\r\n", DEFAULT_TIMEOUT * 3)) {
    return -1;
  }
  if (checkSIMStatus()) {
    return -1;
  }
  return 0;

}

uint32_t GPRS::str_to_ip(const char* str)
{
  uint32_t ip = 0;
  char *p = (char*)str;

  for (int i = 0; i < 4; i++) {
    ip |= atoi(p);
    p = strchr(p, '.');
    if (p == NULL) {
      break;
    }
    if (i < 3) ip <<= 8;
    p++;
  }
  return ip;
}

//HACERR lo de la IP gasta muuuucho espacio (ver .h y todo esto)
char* GPRS::getIPAddress()
{
  uint8_t a = (_ip >> 24) & 0xff;
  uint8_t b = (_ip >> 16) & 0xff;
  uint8_t c = (_ip >> 8) & 0xff;
  uint8_t d = _ip & 0xff;

  snprintf(ip_string, sizeof(ip_string), "%d.%d.%d.%d", a, b, c, d);
  return ip_string;
}

int GPRS::checkSIMStatus(void)
{
  char gprsBuffer[32];
  int count = 0;
  cleanBuffer(gprsBuffer, 32);
  while (count < 3) {
    sendCmd("AT+CPIN?\r\n");
    readBuffer(gprsBuffer, 32, DEFAULT_TIMEOUT);
    if ((NULL != strstr(gprsBuffer, "+CPIN: READY"))) {
      break;
    }
    count++;
    delay(300);
  }
  if (count == 3) {
    return -1;
  }
  return 0;
}

int GPRS::networkCheck(void)
{
  delay(1000);
  if (0 != sendCmdAndWaitForResp("AT+CGREG?\r\n", "+CGREG: 0,1", DEFAULT_TIMEOUT * 3)) {
    ERROR("ERROR:CGREG");
    return -1;
  }
  delay(1000);
  if (0 != sendCmdAndWaitForResp("AT+CGATT?\r\n", "+CGATT: 1", DEFAULT_TIMEOUT)) {
    ERROR("ERROR:CGATT");
    return -1;
  }
  return 0;
}

int GPRS::connectTCP(const char *ip, int port)
{
  char cipstart[50];
  sprintf(cipstart, "AT+CIPSTART=\"TCP\",\"%s\",\"%d\"\r\n", ip, port);
  if (0 != sendCmdAndWaitForResp(cipstart, "CONNECT\r\n", 2 * DEFAULT_TIMEOUT)) { // connect tcp
    ERROR("ERROR:CIPSTART");
    return -1;
  }
  return 0;
}

int GPRS::closeTCP(void)
{
  sendCmd("AT+CIPCLOSE\r\n");
  return 0;
}

int GPRS::shutTCP(void)
{
  if (0 != sendCmdAndWaitForResp("AT+CIPSHUT\r\n", "SHUT OK",  DEFAULT_TIMEOUT)) {
    ERROR("ERROR:+CIPSHUT");
    return -1;
  }
  return 0;
}

int GPRS::quitSerialNet(void)
{
  if (0 != sendCmdAndWaitForResp("+++", "OK", DEFAULT_TIMEOUT)) {
    if (0 != sendCmdAndWaitForResp("+++\r\n", "+++",  DEFAULT_TIMEOUT)) {
      ERROR("ERROR:+++");
      return -1;
    }
  }
  return 0;
}

int GPRS::startSerialNet(void)
{
  if (0 != sendCmdAndWaitForResp("AT+CIPMODE?\r\n", "CIPMODE: 0",  DEFAULT_TIMEOUT)) {
    if (0 != sendCmdAndWaitForResp("AT+CIPMODE=1\r\n", "OK",  DEFAULT_TIMEOUT)) {
      ERROR("ERROR:CIPMODE");
      return -1;
    }
  }
  return 0;
}

int GPRS::getSerialNetData(uint8_t* data)
{
  int len = 0;
  char gprsBuffer[64];
  data = new uint8_t[len];
  unsigned long timerStart, timerEnd;
  timerStart = millis();
  while (1) {
    if (Serial.available()) {
      gprsBuffer[len++] = Serial.read();
    }
    timerEnd = millis();
    if (timerEnd - timerStart > 100) {
      data = new uint8_t[len];
      for (int i = 0; i < len; i++) {
        Serial.print(data[i], HEX);
        Serial.print(" ");
        data[i] = gprsBuffer[i];
      }
      Serial.print(", ");
      Serial.println(len);
      return len;
    }
  }
  return len;
}
