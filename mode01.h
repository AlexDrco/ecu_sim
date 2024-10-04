#ifndef MODE01_H
#define MODE01_H

#include "mcp2515_can.h"

void initRandomSeed() {
  randomSeed(analogRead(0));  // Use an unconnected analog pin to seed the random number generator
}

// Function to generate a random value within a range, with a 40% chance to modify
unsigned char randomValueInRange(unsigned char originalValue, int range) {
  // Randomly decide whether to modify the value (40% chance)
  if (rand() % 2 != 0) {
    return originalValue;  // Return the original value without modification
  }

  // Generate a small random change within the range
  int change = (rand() % (2 * range + 1)) - range;

  int newValue = originalValue + change;

  // Ensure the values stay within the valid range for unsigned char (0-255)
  if (newValue < 0)
    newValue = 0;
  if (newValue > 125)
    newValue = 125;

  return (unsigned char)newValue;
}

unsigned char NoDataResponse[3] = { 0x03, 0x7F, 0x11 };  // No Data Response

// START PIDS
unsigned char SupportedPIDs1[7] = { 0x06, 0x41, 0x00, 0xFF, 0xFF, 0xFF, 0xFF };                       // PID 00 - Bit Encoded;
unsigned char MilCleared[7] = { 0x06, 0x41, 0x01, 0x00, 0x07, 0xE1, 0xFF };                           // PID 01 - Bit Encoded
unsigned char FreezeDTC[7] = { 0x06, 0x41, 0x02, 0x32, 0x00, 0xB9, 0x93 };                            // PID 02 - Special
unsigned char FuelSystemStatus[7] = { 0x06, 0x41, 0x03, 0x32, 0x00, 0xB9, 0x93 };                     // PID 03 - String, Current Value: 32
unsigned char EngineLoad[7] = { 0x06, 0x41, 0x04, 0x20, 0x00, 0xB9, 0x93 };                           // PID 04 - Unit % (0-100), Current Value: 32%
unsigned char CoolantTemp[7] = { 0x06, 0x41, 0x05, 0x5A, 0x00, 0xB9, 0x93 };                          // PID 05 - Unit °C (-40-215), Current Value: 90°C
unsigned char ShortFuelTrim1[7] = { 0x06, 0x41, 0x06, 0x7E, 0x00, 0xB9, 0x93 };                       // PID 06 - Unit % (-100-99.2), Current Value: 0%
unsigned char LongFuelTrim1[7] = { 0x06, 0x41, 0x07, 0x7E, 0x00, 0xB9, 0x93 };                        // PID 07 - Unit % (-100-99.2), Current Value: 0%
unsigned char ShortFuelTrim2[7] = { 0x06, 0x41, 0x08, 0x7E, 0x00, 0xB9, 0x93 };                       // PID 08 - Unit % (-100-99.2), Current Value: 0%
unsigned char LongFuelTrim2[7] = { 0x06, 0x41, 0x09, 0x7E, 0x00, 0xB9, 0x93 };                        // PID 09 - Unit % (-100-99.2), Current Value: 0%
unsigned char MAFSensor[7] = { 0x06, 0x41, 0x10, 0x05, 0x00, 0xB9, 0x93 };                            // PID 10 - Unit g/s (0-655.35), Current Value: 5 g/s
unsigned char FuelPressure[7] = { 0x06, 0x41, 0x0A, 0x28, 0x00, 0xB9, 0x93 };                         // PID 0A - Unit kPa (0-765), Current Value: 40 kPa
unsigned char IntakePressure[7] = { 0x06, 0x41, 0x0B, 0x1E, 0x00, 0xB9, 0x93 };                       // PID 0B - Unit kPa (0-255), Current Value: 30 kPa
unsigned char rpm[7] = { 0x06, 0x41, 0x0C, 0x0C, 0x38, 0xB9, 0x93 };                                  // PID 0C - Unit RPM (0-16383.75), Current Value: 782 RPM
unsigned char vspeed[7] = { 0x06, 0x41, 0x0D, 0x00, 0xE0, 0xB9, 0x93 };                               // PID 0D - Unit km/h (0-255), Current Value: 0 km/h
unsigned char TimingAdvance[7] = { 0x06, 0x41, 0x0E, 0x0A, 0x00, 0xB9, 0x93 };                        // PID 0E - Unit ° (-64-63.5), Current Value: 1.25°
unsigned char IntakeAirTemp[7] = { 0x06, 0x41, 0x0F, 0x19, 0x00, 0xB9, 0x93 };                        // PID 0F - Unit °C (-40-215), Current Value: 25°C
unsigned char ThrottlePos[7] = { 0x06, 0x41, 0x11, 0x1E, 0x00, 0xB9, 0x93 };                          // PID 11 - Unit % (0-100), Current Value: 12.5%
unsigned char Cmdd2ndAirStatus[7] = { 0x06, 0x41, 0x12, 0x01, 0x00, 0xB9, 0x93 };                     // PID 12 - String, Current Value: 1
unsigned char O2Sensors[7] = { 0x06, 0x41, 0x13, 0x03, 0x00, 0xB9, 0x93 };                            // PID 13 - Bit Encoded, Current Value: 3
unsigned char O2B1S1[7] = { 0x06, 0x41, 0x14, 0x2D, 0x00, 0xB9, 0x93 };                               // PID 14 - Unit V (0-1.275), Current Value: 0.45V
unsigned char O2B1S2[7] = { 0x06, 0x41, 0x15, 0x2D, 0x00, 0xB9, 0x93 };                               // PID 15 - Unit V (0-1.275), Current Value: 0.45V
unsigned char O2B1S3[7] = { 0x06, 0x41, 0x16, 0x2D, 0x00, 0xB9, 0x93 };                               // PID 16 - Unit V (0-1.275), Current Value: 0.45V
unsigned char O2B1S4[7] = { 0x06, 0x41, 0x17, 0x2D, 0x00, 0xB9, 0x93 };                               // PID 17 - Unit V (0-1.275), Current Value: 0.45V
unsigned char O2B2S1[7] = { 0x06, 0x41, 0x18, 0x2D, 0x00, 0xB9, 0x93 };                               // PID 18 - Unit V (0-1.275), Current Value: 0.45V
unsigned char O2B2S2[7] = { 0x06, 0x41, 0x19, 0x2D, 0x00, 0xB9, 0x93 };                               // PID 19 - Unit V (0-1.275), Current Value: 0.45V
unsigned char SupportedPIDs2[7] = { 0x06, 0x41, 0x20, 0xFF, 0xFF, 0xFF, 0xFF };                       // PID 20 - Bit Encoded;
unsigned char O2B2S3[7] = { 0x06, 0x41, 0x1A, 0x2D, 0x00, 0xB9, 0x93 };                               // PID 1A - Unit V (0-1.275), Current Value: 0.45V
unsigned char O2B2S4[7] = { 0x06, 0x41, 0x1B, 0x2D, 0x00, 0xB9, 0x93 };                               // PID 1B - Unit V (0-1.275), Current Value: 0.45V
unsigned char OBDCompliance[7] = { 0x06, 0x41, 0x1C, 0x01, 0x00, 0xB9, 0x93 };                        // PID 1C - Bit Encoded, Current Value: 1
unsigned char O2SensorsAlt[7] = { 0x06, 0x41, 0x1D, 0x03, 0x00, 0xB9, 0x93 };                         // PID 1D - Bit Encoded, Current Value: 3
unsigned char AuxInputStatus[7] = { 0x06, 0x41, 0x1E, 0x01, 0x00, 0xB9, 0x93 };                       // PID 1E - Bit Encoded, Current Value: 1
unsigned char RunTime[7] = { 0x06, 0x41, 0x1F, 0xD7, 0xD7 };                                          // PID 1F - Unit seconds (300-2000)
unsigned char FuelRailPressure[7] = { 0x06, 0x41, 0x22, 0x1F4, 0x00, 0xB9, 0x93 };                    // PID 22 - Unit kPa (0-5177.265), Current Value: 500 kPa
unsigned char FuelRailGaugePressure[7] = { 0x06, 0x41, 0x23, 0x3E8, 0x00, 0xB9, 0x93 };               // PID 23 - Unit kPa (0-655350), Current Value: 1000 kPa
unsigned char O2S1WRVoltage[7] = { 0x06, 0x41, 0x24, 0x40, 0x00, 0xB9, 0x93 };                        // PID 24 - Unit V (0-8), Current Value: 2.0V
unsigned char O2S2WRVoltage[7] = { 0x06, 0x41, 0x25, 0x40, 0x00, 0xB9, 0x93 };                        // PID 25 - Unit V (0-8), Current Value: 2.0V
unsigned char O2S3WRVoltage[7] = { 0x06, 0x41, 0x26, 0x40, 0x00, 0xB9, 0x93 };                        // PID 26 - Unit V (0-8), Current Value: 2.0V
unsigned char O2S4WRVoltage[7] = { 0x06, 0x41, 0x27, 0x40, 0x00, 0xB9, 0x93 };                        // PID 27 - Unit V (0-8), Current Value: 2.0V
unsigned char O2S5WRVoltage[7] = { 0x06, 0x41, 0x28, 0x40, 0x00, 0xB9, 0x93 };                        // PID 28 - Unit V (0-8), Current Value: 2.0V
unsigned char O2S6WRVoltage[7] = { 0x06, 0x41, 0x29, 0x40, 0x00, 0xB9, 0x93 };                        // PID 29 - Unit V (0-8), Current Value: 2.0V
unsigned char O2S7WRVoltage[7] = { 0x06, 0x41, 0x2A, 0x40, 0x00, 0xB9, 0x93 };                        // PID 2A - Unit V (0-8), Current Value: 2.0V
unsigned char O2S8WRVoltage[7] = { 0x06, 0x41, 0x2B, 0x40, 0x00, 0xB9, 0x93 };                        // PID 2B - Unit V (0-8), Current Value: 2.0V
unsigned char CommandedEGR[7] = { 0x06, 0x41, 0x2C, 0x14, 0x00, 0xB9, 0x93 };                         // PID 2C - Unit % (0-100), Current Value: 20%
unsigned char EGRError[7] = { 0x06, 0x41, 0x2D, 0x7E, 0x00, 0xB9, 0x93 };                             // PID 2D - Unit % (-100-99.2), Current Value: 0%
unsigned char EvaporativePurge[7] = { 0x06, 0x41, 0x2E, 0x14, 0x00, 0xB9, 0x93 };                     // PID 2E - Unit % (0-100), Current Value: 20%
unsigned char FuelLevel[7] = { 0x06, 0x41, 0x2F, 0x64, 0x00, 0xB9, 0x93 };                            // PID 2F - Unit % (0-100), Current Value: 100%
unsigned char WarmupsSinceDTC[7] = { 0x06, 0x41, 0x30, 0x0A, 0x00, 0xB9, 0x93 };                      // PID 30 - Unit count (0-255), Current Value: 10
unsigned char DistanceSinceDTC[7] = { 0x06, 0x41, 0x31, 0xD7, 0xD7 };                                 // Clr Dist PID 31 - Unit miles (80-200)
unsigned char EvapVPressure[7] = { 0x06, 0x41, 0x32, 0x00, 0x00, 0xB9, 0x93 };                        // PID 32 - Unit Pa (-8192-8191.75), Current Value: 0 Pa
unsigned char BarometricPressure[7] = { 0x06, 0x41, 0x33, 0x1E, 0x00, 0xB9, 0x93 };                   // PID 33 - Unit kPa (0-255), Current Value: 30 kPa
unsigned char O2S1WRCurr[7] = { 0x06, 0x41, 0x34, 0x00, 0x00, 0xB9, 0x93 };                           // PID 34 - Unit mA (-128-128), Current Value: 0 mA
unsigned char O2S2WRCurr[7] = { 0x06, 0x41, 0x35, 0x00, 0x00, 0xB9, 0x93 };                           // PID 35 - Unit mA (-128-128), Current Value: 0 mA
unsigned char O2S3WRCurr[7] = { 0x06, 0x41, 0x36, 0x00, 0x00, 0xB9, 0x93 };                           // PID 36 - Unit mA (-128-128), Current Value: 0 mA
unsigned char O2S4WRCurr[7] = { 0x06, 0x41, 0x37, 0x00, 0x00, 0xB9, 0x93 };                           // PID 37 - Unit mA (-128-128), Current Value: 0 mA
unsigned char O2S5WRCurr[7] = { 0x06, 0x41, 0x38, 0x00, 0x00, 0xB9, 0x93 };                           // PID 38 - Unit mA (-128-128), Current Value: 0 mA
unsigned char O2S6WRCurr[7] = { 0x06, 0x41, 0x39, 0x00, 0x00, 0xB9, 0x93 };                           // PID 39 - Unit mA (-128-128), Current Value: 0 mA
unsigned char O2S7WRCurr[7] = { 0x06, 0x41, 0x3A, 0x00, 0x00, 0xB9, 0x93 };                           // PID 3A - Unit mA (-128-128), Current Value: 0 mA
unsigned char O2S8WRCurr[7] = { 0x06, 0x41, 0x3B, 0x00, 0x00, 0xB9, 0x93 };                           // PID 3B - Unit mA (-128-128), Current Value: 0 mA
unsigned char CatalystTempB1S1[7] = { 0x06, 0x41, 0x3C, 0x01, 0x90, 0xB9, 0x93 };                     // PID 3C - Unit °C (-40-6513.5), Current Value: 400°C
unsigned char CatalystTempB2S1[7] = { 0x06, 0x41, 0x3D, 0x01, 0x90, 0xB9, 0x93 };                     // PID 3D - Unit °C (-40-6513.5), Current Value: 400°C
unsigned char CatalystTempB1S2[7] = { 0x06, 0x41, 0x3E, 0x01, 0x90, 0xB9, 0x93 };                     // PID 3E - Unit °C (-40-6513.5), Current Value: 400°C
unsigned char CatalystTempB2S2[7] = { 0x06, 0x41, 0x3F, 0x01, 0x90, 0xB9, 0x93 };                     // PID 3F - Unit °C (-40-6513.5), Current Value: 400°C
unsigned char SupportedPIDs3[7] = { 0x06, 0x41, 0x40, 0xFF, 0xFF, 0xFF, 0xFF };                        // PID 40 - Bit Encoded;
unsigned char MonitorStatus[7] = { 0x06, 0x41, 0x41, 0x00, 0x00, 0xB9, 0x93 };                        // PID 41 - Bit Encoded, Current Value: 0
unsigned char ControlModuleVoltage[7] = { 0x06, 0x41, 0x42, 0x0C, 0x00, 0xB9, 0x93 };                 // PID 42 - Unit V (0-65.535), Current Value: 12V
unsigned char AbsoluteLoad[7] = { 0x06, 0x41, 0x43, 0x1E, 0x00, 0xB9, 0x93 };                         // PID 43 - Unit % (0-25700), Current Value: 30%
unsigned char CommandedEquivRatio[7] = { 0x06, 0x41, 0x44, 0x80, 0x00, 0xB9, 0x93 };                  // PID 44 - Ratio (0-2), Current Value: 1.0
unsigned char RelativeThrottlePos[7] = { 0x06, 0x41, 0x45, 0x1E, 0x00, 0xB9, 0x93 };                  // PID 45 - Unit % (0-100), Current Value: 30%
unsigned char AmbientAirTemp[7] = { 0x06, 0x41, 0x25, 0x46, 0x00, 0xB9, 0x93 };                       // PID 46 - Unit °C (-40-215), Current Value: 25°C
unsigned char ThrottlePosB[7] = { 0x06, 0x41, 0x47, 0x1E, 0x00, 0xB9, 0x93 };                         // PID 47 - Unit % (0-100), Current Value: 30%
unsigned char ThrottlePosC[7] = { 0x06, 0x41, 0x48, 0x1E, 0x00, 0xB9, 0x93 };                         // PID 48 - Unit % (0-100), Current Value: 30%
unsigned char AcceleratorPosD[7] = { 0x06, 0x41, 0x49, 0x1E, 0x00, 0xB9, 0x93 };                      // PID 49 - Unit % (0-100), Current Value: 30%
unsigned char AcceleratorPosE[7] = { 0x06, 0x41, 0x4A, 0x1E, 0x00, 0xB9, 0x93 };                      // PID 4A - Unit % (0-100), Current Value: 30%
unsigned char AcceleratorPosF[7] = { 0x06, 0x41, 0x4B, 0x1E, 0x00, 0xB9, 0x93 };                      // PID 4B - Unit % (0-100), Current Value: 30%
unsigned char ThrottleActuator[7] = { 0x06, 0x41, 0x4C, 0x1E, 0x00, 0xB9, 0x93 };                     // PID 4C - Unit % (0-100), Current Value: 30%
unsigned char TimeSinceDTC[7] = { 0x06, 0x41, 0x4E, 0xD7, 0xD7 };                                     // Clr Time PID 4E - Unit seconds (8-20 hours)
unsigned char MaxFuelAirEquivalence[7] = { 0x06, 0x41, 0x4F, 0x80, 0x00, 0xB9, 0x93 };                // PID 4F - Ratio (0-2), Current Value: 1.0
unsigned char MaxMAF[7] = { 0x06, 0x41, 0x50, 0x32, 0x00, 0xB9, 0x93 };                               // PID 50 - Unit g/s (0-655.35), Current Value: 50 g/s
unsigned char FuelType[7] = { 0x06, 0x41, 0x51, 0x01, 0x00, 0xB9, 0x93 };                             // PID 51 - String, Current Value: 1 (Gasoline)
unsigned char EthanolPercent[7] = { 0x06, 0x41, 0x52, 0x00, 0x00, 0xB9, 0x93 };                       // PID 52 - Unit % (0-100), Current Value: 0%
unsigned char AbsEvapVPressure[7] = { 0x06, 0x41, 0x53, 0x00, 0x00, 0xB9, 0x93 };                     // PID 52 - Unit Pa (-8192-8191.75), Current Value: 0 Pa
unsigned char EvapVPressureAlt[7] = { 0x06, 0x41, 0x54, 0x00, 0x00, 0xB9, 0x93 };                     // PID 54 - Unit Pa (-8192-8191.75), Current Value: 0 Pa
unsigned char ShortO2TrimB1[7] = { 0x06, 0x41, 0x55, 0x7E, 0x00, 0xB9, 0x93 };                        // PID 55 - Unit % (-100-99.2), Current Value: 0%
unsigned char LongO2TrimB1[7] = { 0x06, 0x41, 0x56, 0x7E, 0x00, 0xB9, 0x93 };                         // PID 56 - Unit % (-100-99.2), Current Value: 0%
unsigned char ShortO2TrimB2[7] = { 0x06, 0x41, 0x57, 0x7E, 0x00, 0xB9, 0x93 };                        // PID 57 - Unit % (-100-99.2), Current Value: 0%
unsigned char LongO2TrimB2[7] = { 0x06, 0x41, 0x58, 0x7E, 0x00, 0xB9, 0x93 };                         // PID 58 - Unit % (-100-99.2), Current Value: 0%
unsigned char FuelRailPressureAbs[7] = { 0x06, 0x41, 0x59, 0x3E8, 0x00, 0xB9, 0x93 };                 // PID 59 - Unit kPa (0-655350), Current Value: 1000 kPa
unsigned char RelAccelPos[7] = { 0x06, 0x41, 0x5A, 0x1E, 0x00, 0xB9, 0x93 };                          // PID 5A - Unit % (0-100), Current Value: 30%
unsigned char HybridBatteryRemaining[7] = { 0x06, 0x41, 0x5B, 0x64, 0x00, 0xB9, 0x93 };               // PID 5B - Unit % (0-100), Current Value: 100%
unsigned char OilTemp[7] = { 0x06, 0x41, 0x5C, 0x19, 0x00, 0xB9, 0x93 };                              // PID 5C - Unit °C (-40-215), Current Value: 25°C
unsigned char FuelInjecTiming[7] = { 0x06, 0x41, 0x5D, 0x00, 0x00, 0xB9, 0x93 };                      // PID 5D - Unit ° (-210.9375-301.9921875), Current Value: 0°
unsigned char FuelRate[7] = { 0x06, 0x41, 0x5E, 0x00, 0x00, 0xB9, 0x93 };                             // PID 5E - Unit L/h (0-3212.75), Current Value: 0 L/h
unsigned char EmisionRequirements[7] = { 0x06, 0x41, 0x5F, 0x00, 0x00, 0xB9, 0x93 };                  // PID 5F - Bit Encoded, Current Value: 0
unsigned char SupportedPIDs4[7] = { 0x06, 0x41, 0x60, 0xFF, 0xFF, 0xFF, 0xFF };                       // PID 60 - Bit Encoded;
unsigned char DemandEngineTorque[7] = { 0x06, 0x41, 0x61, 0x00, 0x00, 0xB9, 0x93 };                   // PID 61 - Unit Nm (-210.9375-301.9921875), Current Value: 0 Nm
unsigned char ActEngineTorque[7] = { 0x06, 0x41, 0x62, 0x00, 0x00, 0xB9, 0x93 };                      // PID 62 - Unit Nm (-210.9375-301.9921875), Current Value: 0 Nm
unsigned char EngineRefTorque[7] = { 0x06, 0x41, 0x63, 0x00, 0x00, 0xB9, 0x93 };                      // PID 63 - Unit Nm (-210.9375-301.9921875), Current Value: 0 Nm
unsigned char EnginePercentTorque[7] = { 0x06, 0x41, 0x64, 0x1E, 0x00, 0xB9, 0x93 };                  // PID 64 - Unit % (0-100), Current Value: 30%
unsigned char AuxillaryInputStatus[7] = { 0x06, 0x41, 0x65, 0x32, 0x00, 0xB9, 0x93 };                 // PID 65 - Special
unsigned char MassAirFlow[7] = { 0x06, 0x41, 0x27, 0x66, 0x00, 0xB9, 0x93 };                          // PID 66 - Unit g/s (0-655.35), Current Value: 5 g/s
unsigned char EngineCoolantTemp[7] = { 0x06, 0x41, 0x67, 0x5A, 0x00, 0xB9, 0x93 };                    // PID 67 - Unit °C (-40-215), Current Value: 90°C
unsigned char IntakeAirTemp2[7] = { 0x06, 0x41, 0x68, 0x19, 0x00, 0xB9, 0x93 };                       // PID 68 - Unit °C (-40-215), Current Value: 25°C
unsigned char ExhaustGasTempB1S1[9] = { 0x06, 0x41, 0x78, 0x0F, 0x0D, 0xD8, 0x0D, 0xD8, 0x0D };       // PID 78 - EGT Bank 1, Idle Value: 300°C
unsigned char ExhaustGasTempB2S1[9] = { 0x06, 0x41, 0x79, 0x0F, 0x0D, 0xD8, 0x0D, 0xD8, 0x0D };       // PID 79 - EGT Bank 2, Idle Value: 300°C
unsigned char DieselParticulateFilter[7] = { 0x06, 0x41, 0x7C, 0x14, 0x00, 0xB9, 0x93 };              // PID 7C - DPF, Idle Value: 20%
unsigned char DieselEnginetTotalHours[9] = { 0x06, 0x41, 0x7F, 0x00, 0x05, 0x7E, 0x40, 0xB9, 0x93 };  // PID 7F - Engine Hours, Idle Value: 100 hours
unsigned char SupportedPIDs5[7] = { 0x06, 0x41, 0x80, 0xFF, 0xFF, 0xFF, 0xFF };                        // PID 80 - Bit Encoded;
unsigned char SupportedPIDs6[7] = { 0x06, 0x41, 0xA0, 0xFF, 0xFF, 0xFF, 0xFF };                        // PID A0 - Bit Encoded;
unsigned char CylinderFuelRate[6] = { 0x06, 0x41, 0xA2, 0x3E, 0x80 };                                 // PID A2 - Cylinder Fuel Rate, Idle Value: 500 mg/stroke
unsigned char EvapSystemVaporPressure[6] = { 0x06, 0x41, 0xA3, 0x03, 0xE8 };                          // PID A3 - Evap System Vapor Pressure, Idle Value: 1000 Pa
unsigned char TransmissionActualGear[6] = { 0x06, 0x41, 0xA4, 0x01, 0x05, 0xDC };                     // PID A4 - Transmission Actual Gear, Idle Value: 1.5 ratio
unsigned char CommandedDieselExhaustFluidDosing[5] = { 0x06, 0x41, 0xA5, 0x01, 0x64 };                // PID A5 - Commanded Diesel Exhaust Fluid Dosing, Idle Value: 50%
unsigned char Odometer[8] = { 0x06, 0x41, 0xA6, 0x00, 0x0F, 0x42, 0x40 };                             // PID A6 - Odometer, Idle Value: 100,000 km
unsigned char SupportedPIDs7[7] = { 0x06, 0x41, 0xC0, 0x00, 0x00, 0x00, 0x00 };                       // PID C0 - Bit Encoded;
// END PIDS

// Static values
unsigned char MilDistance[7] = { 0x06, 0x41, 0x21, 0x00, 0x00, 0x00, 0x00 };                          // MIL Dist PID 21 - Unit km (0-65535), Current Value: 0 km
unsigned char RunTimeMIL[7] = { 0x06, 0x41, 0x4D, 0x00, 0x00, 0x00, 0x00 };                           // Mil Time PID 4D - Unit seconds (0-65535), Current Value: 0 seconds

void handleMode01(unsigned char *buf, mcp2515_can &CAN) {
  switch (buf[2]) {
    case 0x00:
      CAN.sendMsgBuf(0x7E8, 0, 7, SupportedPIDs1);
      break;
    case 0x01:
      CAN.sendMsgBuf(0x7E8, 0, 7, MilCleared);
      break;
    case 0x02:
      CAN.sendMsgBuf(0x7E8, 0, 7, FreezeDTC);
      break;
    case 0x03:
      CAN.sendMsgBuf(0x7E8, 0, 7, FuelSystemStatus);
      break;
    case 0x04:
      EngineLoad[3] = randomValueInRange(EngineLoad[3], 1);  // Adjust the range as needed
      CAN.sendMsgBuf(0x7E8, 0, 7, EngineLoad);
      break;
    case 0x05:
      CoolantTemp[4] = randomValueInRange(CoolantTemp[4], 10);  // Adjust the range as needed
      CAN.sendMsgBuf(0x7E8, 0, 7, CoolantTemp);
      break;
    case 0x06:
      ShortFuelTrim1[4] = randomValueInRange(ShortFuelTrim1[4], 10);
      CAN.sendMsgBuf(0x7E8, 0, 7, ShortFuelTrim1);
      break;
    case 0x07:
      LongFuelTrim1[4] = randomValueInRange(LongFuelTrim1[4], 10);
      CAN.sendMsgBuf(0x7E8, 0, 7, LongFuelTrim1);
      break;
    case 0x08:
      ShortFuelTrim2[4] = randomValueInRange(ShortFuelTrim2[4], 10);
      CAN.sendMsgBuf(0x7E8, 0, 7, ShortFuelTrim2);
      break;
    case 0x09:
      LongFuelTrim1[4] = randomValueInRange(LongFuelTrim1[4], 10);
      CAN.sendMsgBuf(0x7E8, 0, 7, LongFuelTrim2);
      break;
    case 0x0A:
      FuelPressure[4] = randomValueInRange(FuelPressure[4], 10);
      CAN.sendMsgBuf(0x7E8, 0, 7, FuelPressure);
      break;
    case 0x0B:
      IntakePressure[4] = randomValueInRange(IntakePressure[4], 10);
      CAN.sendMsgBuf(0x7E8, 0, 7, IntakePressure);
      break;
    case 0x0C:
      rpm[4] = randomValueInRange(rpm[4], 10);
      CAN.sendMsgBuf(0x7E8, 0, 7, rpm);
      break;
    case 0x0D:
      CAN.sendMsgBuf(0x7E8, 0, 7, vspeed);
      break;
    case 0x0E:
      CAN.sendMsgBuf(0x7E8, 0, 7, TimingAdvance);
      break;
    case 0x0F:
      IntakeAirTemp[4] = randomValueInRange(IntakeAirTemp[4], 10);
      CAN.sendMsgBuf(0x7E8, 0, 7, IntakeAirTemp);
      break;
    case 0x10:
      MAFSensor[4] = randomValueInRange(MAFSensor[4], 10);
      CAN.sendMsgBuf(0x7E8, 0, 7, MAFSensor);
      break;
    case 0x11:
      CAN.sendMsgBuf(0x7E8, 0, 7, ThrottlePos);
      break;
    case 0x12:
      CAN.sendMsgBuf(0x7E8, 0, 7, Cmdd2ndAirStatus);
      break;
    case 0x13:
      CAN.sendMsgBuf(0x7E8, 0, 7, O2Sensors);
      break;
    case 0x14:
      CAN.sendMsgBuf(0x7E8, 0, 7, O2B1S1);
      break;
    case 0x15:
      CAN.sendMsgBuf(0x7E8, 0, 7, O2B1S2);
      break;
    case 0x16:
      CAN.sendMsgBuf(0x7E8, 0, 7, O2B1S3);
      break;
    case 0x17:
      CAN.sendMsgBuf(0x7E8, 0, 7, O2B1S4);
      break;
    case 0x18:
      CAN.sendMsgBuf(0x7E8, 0, 7, O2B2S1);
      break;
    case 0x19:
      CAN.sendMsgBuf(0x7E8, 0, 7, O2B2S2);
      break;
    case 0x1A:
      CAN.sendMsgBuf(0x7E8, 0, 7, O2B2S3);
      break;
    case 0x1B:
      CAN.sendMsgBuf(0x7E8, 0, 7, O2B2S4);
      break;
    case 0x1C:
      CAN.sendMsgBuf(0x7E8, 0, 7, OBDCompliance);
      break;
    case 0x1D:
      CAN.sendMsgBuf(0x7E8, 0, 7, O2SensorsAlt);
      break;
    case 0x1E:
      CAN.sendMsgBuf(0x7E8, 0, 7, AuxInputStatus);
      break;
    case 0x1F:
      CAN.sendMsgBuf(0x7E8, 0, 7, RunTime);
      break;
    case 0x20:
      CAN.sendMsgBuf(0x7E8, 0, 7, SupportedPIDs2);
      break;
    case 0x21:
      CAN.sendMsgBuf(0x7E8, 0, 7, MilDistance);
      break;
    case 0x22:
      CAN.sendMsgBuf(0x7E8, 0, 7, FuelRailPressure);
      break;
    case 0x23:
      CAN.sendMsgBuf(0x7E8, 0, 7, FuelRailGaugePressure);
      break;
    case 0x24:
      CAN.sendMsgBuf(0x7E8, 0, 7, O2S1WRVoltage);
      break;
    case 0x25:
      CAN.sendMsgBuf(0x7E8, 0, 7, O2S2WRVoltage);
      break;
    case 0x26:
      CAN.sendMsgBuf(0x7E8, 0, 7, O2S3WRVoltage);
      break;
    case 0x27:
      CAN.sendMsgBuf(0x7E8, 0, 7, O2S4WRVoltage);
      break;
    case 0x28:
      CAN.sendMsgBuf(0x7E8, 0, 7, O2S5WRVoltage);
      break;
    case 0x29:
      CAN.sendMsgBuf(0x7E8, 0, 7, O2S6WRVoltage);
      break;
    case 0x2A:
      CAN.sendMsgBuf(0x7E8, 0, 7, O2S7WRVoltage);
      break;
    case 0x2B:
      CAN.sendMsgBuf(0x7E8, 0, 7, O2S8WRVoltage);
      break;
    case 0x2C:
      CAN.sendMsgBuf(0x7E8, 0, 7, CommandedEGR);
      break;
    case 0x2D:
      CAN.sendMsgBuf(0x7E8, 0, 7, EGRError);
      break;
    case 0x2E:
      CAN.sendMsgBuf(0x7E8, 0, 7, EvaporativePurge);
      break;
    case 0x2F:
      CAN.sendMsgBuf(0x7E8, 0, 7, FuelLevel);
      break;
    case 0x30:
      CAN.sendMsgBuf(0x7E8, 0, 7, WarmupsSinceDTC);
      break;
    case 0x31:
      CAN.sendMsgBuf(0x7E8, 0, 7, DistanceSinceDTC);
      break;
    case 0x32:
      EvapVPressure[4] = randomValueInRange(EvapVPressure[4], 10);
      CAN.sendMsgBuf(0x7E8, 0, 7, EvapVPressure);
      break;
    case 0x33:
      BarometricPressure[4] = randomValueInRange(BarometricPressure[4], 10);
      CAN.sendMsgBuf(0x7E8, 0, 7, BarometricPressure);
      break;
    case 0x34:
      CAN.sendMsgBuf(0x7E8, 0, 7, O2S1WRCurr);
      break;
    case 0x35:
      CAN.sendMsgBuf(0x7E8, 0, 7, O2S2WRCurr);
      break;
    case 0x36:
      CAN.sendMsgBuf(0x7E8, 0, 7, O2S3WRCurr);
      break;
    case 0x37:
      CAN.sendMsgBuf(0x7E8, 0, 7, O2S4WRCurr);
      break;
    case 0x38:
      CAN.sendMsgBuf(0x7E8, 0, 7, O2S5WRCurr);
      break;
    case 0x39:
      CAN.sendMsgBuf(0x7E8, 0, 7, O2S6WRCurr);
      break;
    case 0x3A:
      CAN.sendMsgBuf(0x7E8, 0, 7, O2S7WRCurr);
      break;
    case 0x3B:
      CAN.sendMsgBuf(0x7E8, 0, 7, O2S8WRCurr);
      break;
    case 0x3C:
      CatalystTempB1S1[4] = randomValueInRange(CatalystTempB1S1[4], 10);
      CAN.sendMsgBuf(0x7E8, 0, 7, CatalystTempB1S1);
      break;
    case 0x3D:
      CatalystTempB2S1[4] = randomValueInRange(CatalystTempB2S1[4], 10);
      CAN.sendMsgBuf(0x7E8, 0, 7, CatalystTempB2S1);
      break;
    case 0x3E:
      CatalystTempB1S2[4] = randomValueInRange(CatalystTempB1S2[4], 10);
      CAN.sendMsgBuf(0x7E8, 0, 7, CatalystTempB1S2);
      break;
    case 0x3F:
      CatalystTempB2S2[4] = randomValueInRange(CatalystTempB2S2[4], 10);
      CAN.sendMsgBuf(0x7E8, 0, 7, CatalystTempB2S2);
      break;
    case 0x40:
      CAN.sendMsgBuf(0x7E8, 0, 7, SupportedPIDs3);
      break;
    case 0x41:
      CAN.sendMsgBuf(0x7E8, 0, 7, MonitorStatus);
      break;
    case 0x42:
      CAN.sendMsgBuf(0x7E8, 0, 7, ControlModuleVoltage);
      break;
    case 0x43:
      CAN.sendMsgBuf(0x7E8, 0, 7, AbsoluteLoad);
      break;
    case 0x44:
      CAN.sendMsgBuf(0x7E8, 0, 7, CommandedEquivRatio);
      break;
    case 0x45:
      CAN.sendMsgBuf(0x7E8, 0, 7, RelativeThrottlePos);
      break;
    case 0x46:
      CAN.sendMsgBuf(0x7E8, 0, 7, AmbientAirTemp);
      break;
    case 0x47:
      CAN.sendMsgBuf(0x7E8, 0, 7, ThrottlePosB);
      break;
    case 0x48:
      CAN.sendMsgBuf(0x7E8, 0, 7, ThrottlePosC);
      break;
    case 0x49:
      CAN.sendMsgBuf(0x7E8, 0, 7, AcceleratorPosD);
      break;
    case 0x4A:
      CAN.sendMsgBuf(0x7E8, 0, 7, AcceleratorPosE);
      break;
    case 0x4B:
      CAN.sendMsgBuf(0x7E8, 0, 7, AcceleratorPosF);
      break;
    case 0x4C:
      CAN.sendMsgBuf(0x7E8, 0, 7, ThrottleActuator);
      break;
    case 0x4D:
      CAN.sendMsgBuf(0x7E8, 0, 7, RunTimeMIL);
      break;
    case 0x4E:
      CAN.sendMsgBuf(0x7E8, 0, 7, TimeSinceDTC);
      break;
    case 0x50:
      CAN.sendMsgBuf(0x7E8, 0, 7, MaxMAF);
      break;
    case 0x51:
      CAN.sendMsgBuf(0x7E8, 0, 7, FuelType);
      break;
    case 0x52:
      CAN.sendMsgBuf(0x7E8, 0, 7, EthanolPercent);
      break;
    case 0x53:
      CAN.sendMsgBuf(0x7E8, 0, 7, AbsEvapVPressure);
      break;
    case 0x54:
      CAN.sendMsgBuf(0x7E8, 0, 7, EvapVPressureAlt);
      break;
    case 0x55:
      CAN.sendMsgBuf(0x7E8, 0, 7, ShortO2TrimB1);
      break;
    case 0x56:
      CAN.sendMsgBuf(0x7E8, 0, 7, LongO2TrimB1);
      break;
    case 0x57:
      CAN.sendMsgBuf(0x7E8, 0, 7, ShortO2TrimB2);
      break;
    case 0x58:
      CAN.sendMsgBuf(0x7E8, 0, 7, LongO2TrimB2);
      break;
    case 0x59:
      CAN.sendMsgBuf(0x7E8, 0, 7, FuelRailPressureAbs);
      break;
    case 0x5A:
      CAN.sendMsgBuf(0x7E8, 0, 7, RelAccelPos);
      break;
    case 0x5B:
      CAN.sendMsgBuf(0x7E8, 0, 7, HybridBatteryRemaining);
      break;
    case 0x5C:
      CAN.sendMsgBuf(0x7E8, 0, 7, OilTemp);
      break;
    case 0x5D:
      CAN.sendMsgBuf(0x7E8, 0, 7, FuelInjecTiming);
      break;
    case 0x5E:
      CAN.sendMsgBuf(0x7E8, 0, 7, FuelRate);
      break;
    case 0x5F:
      CAN.sendMsgBuf(0x7E8, 0, 7, EmisionRequirements);
      break;
    case 0x60:
      CAN.sendMsgBuf(0x7E8, 0, 7, SupportedPIDs4);
      break;
    case 0x61:
      CAN.sendMsgBuf(0x7E8, 0, 7, DemandEngineTorque);
      break;
    case 0x62:
      CAN.sendMsgBuf(0x7E8, 0, 7, ActEngineTorque);
      break;
    case 0x63:
      CAN.sendMsgBuf(0x7E8, 0, 7, EngineRefTorque);
      break;
    case 0x64:
      CAN.sendMsgBuf(0x7E8, 0, 7, EnginePercentTorque);
      break;
    case 0x65:
      CAN.sendMsgBuf(0x7E8, 0, 7, AuxillaryInputStatus);
      break;
    case 0x66:
      CAN.sendMsgBuf(0x7E8, 0, 7, MassAirFlow);
      break;
    case 0x67:
      CAN.sendMsgBuf(0x7E8, 0, 7, EngineCoolantTemp);
      break;
    case 0x68:
      CAN.sendMsgBuf(0x7E8, 0, 7, IntakeAirTemp2);
      break;
    case 0x69:
      CAN.sendMsgBuf(0x7E8, 0, 7, NoDataResponse);
      break;
    case 0x6A:
      CAN.sendMsgBuf(0x7E8, 0, 7, NoDataResponse);
      break;
    case 0x6B:
      CAN.sendMsgBuf(0x7E8, 0, 7, NoDataResponse);
      break;
    case 0x6C:
      CAN.sendMsgBuf(0x7E8, 0, 7, NoDataResponse);
      break;
    case 0x6D:
      CAN.sendMsgBuf(0x7E8, 0, 7, NoDataResponse);
      break;
    case 0x6E:
      CAN.sendMsgBuf(0x7E8, 0, 7, NoDataResponse);
      break;
    case 0x6F:
      CAN.sendMsgBuf(0x7E8, 0, 7, NoDataResponse);
      break;
    case 0x70:
      CAN.sendMsgBuf(0x7E8, 0, 7, NoDataResponse);
      break;
    case 0x71:
      CAN.sendMsgBuf(0x7E8, 0, 7, NoDataResponse);
      break;
    case 0x72:
      CAN.sendMsgBuf(0x7E8, 0, 7, NoDataResponse);
      break;
    case 0x73:
      CAN.sendMsgBuf(0x7E8, 0, 7, NoDataResponse);
      break;
    case 0x74:
      CAN.sendMsgBuf(0x7E8, 0, 7, NoDataResponse);
      break;
    case 0x75:
      CAN.sendMsgBuf(0x7E8, 0, 7, NoDataResponse);
      break;
    case 0x76:
      CAN.sendMsgBuf(0x7E8, 0, 7, NoDataResponse);
      break;
    case 0x77:
      CAN.sendMsgBuf(0x7E8, 0, 7, NoDataResponse);
      break;
    case 0x78:
      CAN.sendMsgBuf(0x7E8, 0, 9, ExhaustGasTempB1S1);
      break;
    case 0x79:
      CAN.sendMsgBuf(0x7E8, 0, 9, ExhaustGasTempB2S1);
      break;
    case 0x7A:
      CAN.sendMsgBuf(0x7E8, 0, 7, NoDataResponse);
      break;
    case 0x7B:
      CAN.sendMsgBuf(0x7E8, 0, 7, NoDataResponse);
      break;
    case 0x7C:
      CAN.sendMsgBuf(0x7E8, 0, 7, DieselParticulateFilter);
      break;
    case 0x7D:
      CAN.sendMsgBuf(0x7E8, 0, 7, NoDataResponse);
      break;
    case 0x7E:
      CAN.sendMsgBuf(0x7E8, 0, 7, NoDataResponse);
      break;
    case 0x7F:
      CAN.sendMsgBuf(0x7E8, 0, 9, DieselEnginetTotalHours);
      break;
    case 0x80:
      CAN.sendMsgBuf(0x7E8, 0, 7, NoDataResponse);
      break;
    case 0x81:
      CAN.sendMsgBuf(0x7E8, 0, 7, NoDataResponse);
      break;
    case 0xA2:
      CAN.sendMsgBuf(0x7E8, 0, 5, CylinderFuelRate);
      break;
    case 0xA3:
      CAN.sendMsgBuf(0x7E8, 0, 5, EvapSystemVaporPressure);
      break;
    case 0xA4:
      CAN.sendMsgBuf(0x7E8, 0, 6, TransmissionActualGear);
      break;
    case 0xA5:
      CAN.sendMsgBuf(0x7E8, 0, 5, CommandedDieselExhaustFluidDosing);
      break;
    case 0xA6:
      CAN.sendMsgBuf(0x7E8, 0, 8, Odometer);
      break;
    default:
      Serial.println("Unsupported PID for Mode 01");
      CAN.sendMsgBuf(0x7E8, 0, 7, NoDataResponse);
      break;
  }
}

#endif