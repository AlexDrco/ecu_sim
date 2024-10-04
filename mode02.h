#ifndef MODE02_H
#define MODE02_H

#include <mcp2515_can.h>

unsigned char NoDataResponse[7] = { 0x06, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00 };

void handleMode02(unsigned char *buf, mcp2515_can &CAN) {
  CAN.sendMsgBuf(0x7E8, 0, 7, NoDataResponse);
}

#endif