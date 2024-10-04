// ECU-sim/mode09.h

#ifndef MODE09_H
#define MODE09_H

#include "mcp2515_can.h"

// START PIDS
unsigned char SupportedMode9PIDs[8] = {0x06, 0x49, 0x00, 0xFF, 0xFF, 0xFF, 0x00};          // 0x0FF All 09 Commands Supported
unsigned char VINMessageCount[8] = {0x06, 0x49, 0x01, 0x05};                               // Usually the value will be 5
unsigned char CalibrationIDMessageCount[8] = {0x49, 0x03, 0x01};                           // Multiple of 4
unsigned char CVNMessageCount[8] = {0x04, 0x49, 0x05, 0x00};                               // Example count
unsigned char InUsePerformanceSpark[8] = {0x06, 0x49, 0x08, 0x00, 0x00, 0x00, 0x00};       // Example data
unsigned char ECUNameMessageCount[8] = {0x49, 0x09, 0x01};                                 // Example count
unsigned char ECUName[8] = {0x06, 0x49, 0x0A, 0x45, 0x43, 0x55, 0x43, 0x4D};               // Example ECU name
unsigned char InUsePerformanceCompression[8] = {0x06, 0x49, 0x0B, 0x00, 0x00, 0x00, 0x00}; // Example data
// END PIDS

// START CALID
unsigned char CalibrationID1[8] = {0x10, 0x33, 0x49, 0x04, 0x00, 0x00, 0x00, 0x00};
unsigned char CalibrationID2[8] = {0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char CalibrationID3[8] = {0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char CalibrationID4[8] = {0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char CalibrationID5[8] = {0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char CalibrationID6[8] = {0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char CalibrationID7[8] = {0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char CalibrationID8[8] = {0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
// END CALID

// START CVN
unsigned char CVN1[8] = {0x10, 0x0F, 0x49, 0x06, 0x00, 0x00, 0x00, 0x00};
unsigned char CVN2[8] = {0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char CVN3[8] = {0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char CVN4[8] = {0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
// END CVN

// START VIN
unsigned char VINFrame1[8] = {0x10, 0x14, 0x49, 0x02, 0x01, 0x31, 0x46, 0x41};
unsigned char VINFrame2[8] = {0x21, 0x4C, 0x50, 0x36, 0x32, 0x57, 0x34, 0x57};
unsigned char VINFrame3[8] = {0x22, 0x48, 0x31, 0x32, 0x38, 0x37, 0x30, 0x33};
// END VIN

void handleMode09(unsigned char *buf, mcp2515_can &CAN)
{
    switch (buf[2])
    {
    case 0x00:
        Serial.println("Sending Supported Mode 9 PIDs");
        CAN.sendMsgBuf(0x7E8, 0, 8, SupportedMode9PIDs);
        break;
    case 0x01:
        CAN.sendMsgBuf(0x7E8, 0, 8, VINMessageCount);
        break;
    case 0x02:
        CAN.sendMsgBuf(0x7E8, 0, 8, VINFrame1);
        delay(50); // Delay to ensure correct sequence
        CAN.sendMsgBuf(0x7E8, 0, 8, VINFrame2);
        delay(50); // Delay to ensure correct sequence
        CAN.sendMsgBuf(0x7E8, 0, 8, VINFrame3);
        break;
    case 0x03:
        CAN.sendMsgBuf(0x7E8, 0, 8, CalibrationIDMessageCount);
        break;
    case 0x04:
        CAN.sendMsgBuf(0x7E8, 0, 8, CalibrationID1);
        delay(50); // Delay to ensure correct sequence
        CAN.sendMsgBuf(0x7E8, 0, 8, CalibrationID2);
        delay(50); // Delay to ensure correct sequence
        CAN.sendMsgBuf(0x7E8, 0, 8, CalibrationID3);
        delay(50); // Delay to ensure correct sequence
        CAN.sendMsgBuf(0x7E8, 0, 8, CalibrationID4);
        delay(50); // Delay to ensure correct sequence
        CAN.sendMsgBuf(0x7E8, 0, 8, CalibrationID5);
        delay(50); // Delay to ensure correct sequence
        CAN.sendMsgBuf(0x7E8, 0, 8, CalibrationID6);
        delay(50); // Delay to ensure correct sequence
        CAN.sendMsgBuf(0x7E8, 0, 8, CalibrationID7);
        delay(50); // Delay to ensure correct sequence
        CAN.sendMsgBuf(0x7E8, 0, 8, CalibrationID8);
        break;
    case 0x05:
        CAN.sendMsgBuf(0x7E8, 0, 8, CVNMessageCount);
        break;
    case 0x06:
        CAN.sendMsgBuf(0x7E8, 0, 8, CVN1);
        delay(50); // Delay to ensure correct sequence
        CAN.sendMsgBuf(0x7E8, 0, 8, CVN2);
        delay(50); // Delay to ensure correct sequence
        CAN.sendMsgBuf(0x7E8, 0, 8, CVN3);
        delay(50); // Delay to ensure correct sequence
        CAN.sendMsgBuf(0x7E8, 0, 8, CVN4);
        break;
    case 0x07:
        // Add handling for PID 0x07 if needed
        break;
    case 0x08:
        CAN.sendMsgBuf(0x7E8, 0, 8, InUsePerformanceSpark);
        break;
    case 0x09:
        CAN.sendMsgBuf(0x7E8, 0, 8, ECUNameMessageCount);
        break;
    case 0x0A:
        CAN.sendMsgBuf(0x7E8, 0, 8, ECUName);
        break;
    case 0x0B:
        CAN.sendMsgBuf(0x7E8, 0, 8, InUsePerformanceCompression);
        break;
    default:
        Serial.println("Unsupported Mode 09 PID");
        break;
    }
}
#endif