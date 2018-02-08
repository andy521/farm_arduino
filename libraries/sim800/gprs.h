#ifndef __GPRS_H__
#define __GPRS_H__

#include "sim800c.h"

enum Protocol {
    CLOSED = 0,
    TCP    = 1,
    UDP    = 2,
};

/** GPRS class.
 *  used to realize GPRS communication
 */
#define MESSAGE_LENGTH  100

class GPRS: public SIM800C
{
public:
    uint32_t _ip;
    char ip_string[20];

    /** Create GPRS instance
     *  @param number default phone number during mobile communication
     */
    GPRS(int baudRate = 9600):SIM800C(baudRate){};

    /** initialize GPRS module including SIM card check & signal strength
     *  @returns
     *      0 on success
     *      -1 on error
     */
    int init(void);

    /** parse IP string
     *  @return
     *      ip in hex
     */
    uint32_t str_to_ip(const char* str);

    /** get Ip address
     *  @return
     *       IP string
     */
    char* getIPAddress();

    /** check SIM card' Status
     *  @returns
     *      0 on success
     *      -1 on error
     */
    int checkSIMStatus(void);

    /** check network is OK or not
     *  @returns
     *      0 on success
     *      -1 on error
     */
    int networkCheck(void);

    /** build TCP connect
     *  @param  ip  ip address which will connect to
     *  @param  port    TCP server' port number
     *  @returns
     *      0 on success
     *      -1 on error
     */
    int connectTCP(const char* ip, int port);

    /** close TCP connection
     *  @returns
     *      0 on success
     *      -1 on error
     */
    int closeTCP(void);

    /** close TCP service
     *  @returns
     *      0 on success
     *      -1 on error
     */
    int shutTCP(void);

    /**
     * send '+++' to quit serial network
     *  @returns
     *      0 on success
     *      -1 on error
     */
     int quitSerialNet(void);

     /**
      * set serial network model
      */
      int startSerialNet(void);

    /**
     * get data by serial network model
     */
      int getSerialNetData(uint8_t* data);

};
#endif

