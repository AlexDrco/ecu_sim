# Arduino ECU Simulator

A simulated Engine Control Unit (ECU) for Arduino using a CAN Bus shield to mimic responses to OBD-II commands.


## Features

- **Simulate OBD-II Commands**: Respond to PIDs (Parameter IDs) commonly used in automotive diagnostics.
- **CAN Bus Communication**: Utilize the Arduino CAN Bus shield to communicate like a real ECU.
- **Customizable Responses**: Easily tweak the code to mimic different engine conditions or faults.
- **Educational Tool**: Great for learning OBD-II protocols or testing diagnostic tools.

OBD-II (On-Board Diagnostics II) allows for standardized diagnostics of automotive systems. This simulator aims to replicate those diagnostics for educational or development purposes.

> "This ECU simulator provides a bridge between theoretical knowledge of automotive electronics and practical application."


## Required

- **Arduino + Arduino IDE**
- **CAN Bus Shield v2**
- **OBD Female connector**
- **12V power source**


## Usage

To set up your Arduino CAN ECU Simulator:

1. **Hardware Setup**:
   - Connect your Arduino to the CAN Bus shield.
   - 12v only required for powering scanning device.
   
   ![alt text](diagram.jpg)

2. **Software**:

   - Open in Arduino IDE
   - Install Seeduino Can Bus library
   - SPI Pin for CAN Bus Shield is pin 9, other versions use pin 10.