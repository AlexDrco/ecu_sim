#ifndef MODE03_H
#define MODE03_H

#include "mcp2515_can.h"

#define MAX_DTCS 10  // Maximum number of DTCs

unsigned char DTCs[MAX_DTCS * 2] = {
    0x00, 0x01,  // P0001
    0x01, 0x02,  // C0102
    0x02, 0x03,  // B0203
    0x03, 0x04   // U0304
};

int numDTCs = 0;  // Initial number of DTCs

void addDTC(unsigned char highByte, unsigned char lowByte) {
    if (numDTCs < MAX_DTCS) {
        DTCs[numDTCs * 2] = highByte;
        DTCs[numDTCs * 2 + 1] = lowByte;
        numDTCs++;
    } else {
        Serial.println("DTC list is full");
    }
}

void removeDTC(unsigned char highByte, unsigned char lowByte) {
    for (int i = 0; i < numDTCs; i++) {
        if (DTCs[i * 2] == highByte && DTCs[i * 2 + 1] == lowByte) {
            for (int j = i; j < numDTCs - 1; j++) {
                DTCs[j * 2] = DTCs[(j + 1) * 2];
                DTCs[j * 2 + 1] = DTCs[(j + 1) * 2 + 1];
            }
            numDTCs--;
            break;
        }
    }
}

void handleMode03(mcp2515_can& CAN) {
    if (numDTCs == 0) {
        // No DTCs found
        unsigned char response[8] = {0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        CAN.sendMsgBuf(0x7E8, 0, 8, response);
    } else {
        int numFrames = (numDTCs + 2) / 3;  // 3 DTCs per frame

        if (numDTCs <= 2) {
            // Single Frame Response
            unsigned char response[8] = {0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
            response[1] = numDTCs * 2;
            for (int i = 0; i < numDTCs * 2; i++) {
                response[2 + i] = DTCs[i];
            }
            CAN.sendMsgBuf(0x7E8, 0, 8, response);
        } else {
            // Multi-Frame Response
            unsigned char response[8] = {0x10, 0x00, 0x43, 0x00, 0x00, 0x00, 0x00, 0x00};
            response[1] = numDTCs * 2 + 2;
            CAN.sendMsgBuf(0x7E8, 0, 8, response);
            delay(50);

            for (int frame = 1; frame <= numFrames; frame++) {
                response[0] = 0x21 + (frame - 1);
                for (int i = 0; i < 6; i++) {
                    int index = (frame - 1) * 6 + i;
                    if (index < numDTCs * 2) {
                        response[2 + i] = DTCs[index];
                    } else {
                        response[2 + i] = 0x00;
                    }
                }
                CAN.sendMsgBuf(0x7E8, 0, 8, response);
                delay(50);
            }
        }
    }
}

#endif