#define IP_ADDRSS       "172.96.207.128"
#define PORT            20001

GPRS gprs(9600);

void gprsInit() {
  gprs.DSerial.println("Hello World");
  gprs.init();
  while (gprs.quitSerialNet());
  while (gprs.sendAT());
  while (gprs.networkCheck());
  while (gprs.shutTCP());
  while (gprs.startSerialNet());
  while (gprs.connectTCP(IP_ADDRSS, PORT));
}

