#include <SPI.h>
#include "mcp2515_can.h"
#include "mode01.h"
#include "mode03.h"
#include "mode09.h"

const int SPI_CS_PIN = 9;    // Set CS to pin 9 for CAN Bus Shield v2 
mcp2515_can CAN(SPI_CS_PIN); // Create CAN object

unsigned char len = 0;
unsigned char buf[8];


void setup() {
    Serial.begin(115200);

    while (CAN_OK != CAN.begin(CAN_500KBPS)) { // init can bus : baudrate = 500k
        Serial.println("CAN BUS Shield init fail, retry...");
        delay(100);
    }
    Serial.println("CAN BUS Shield init ok!");
}

void loop() {
    if (CAN_MSGAVAIL == CAN.checkReceive()) {
        CAN.readMsgBuf(&len, buf);
        unsigned long canId = CAN.getCanId();

        // Debugging: Print received message
        Serial.print("Received CAN message: ");
        for (int i = 0; i < len; i++) {
            Serial.print(buf[i], HEX);
            Serial.print(" ");
        }
        Serial.println();

        // Check which mode was received and respond accordingly
        if (buf[1] == 1) { // Mode 01
            handleMode01(buf, CAN);
        } else if (buf[1] == 2) { // Mode 02
            handleMode01(buf, CAN);
        } else if (buf[1] == 3) { // Mode 03
            handleMode03(CAN);
        } else if (buf[1] == 9) { // Mode 09
            handleMode09(buf, CAN);
        }
    }
}
