# 260113_ESP8266_32Relay

## Project Introduction

This is a 32-channel relay control project based on ESP8266 microcontroller, supporting remote control of relays via WiFi and MQTT protocol.

## Features

- Supports independent control of 32 channels of relays
- Connects to network via WiFi
- Uses MQTT protocol for remote communication
- Supports turning on and off individual relays
- Can be controlled via MQTT clients (such as MQTTX)
- Provides Arduino IDE compatible sample code

## Hardware Requirements

- ESP8266 development board (such as ESP-12F)
- 32-channel relay module (driven by HC595 shift register)
- HC595 shift register
- Power supply (according to relay module requirements)
- Several connecting wires

## Software Requirements

### Development Environment
- VS Code + PlatformIO plugin
- Or Arduino IDE

### Dependencies
- ESP8266WiFi
- PubSubClient

## Quick Start

### Using VS Code + PlatformIO

1. Clone the entire project to local:
   ```bash
   git clone <repository-url>
   ```

2. Open VS Code and install PlatformIO plugin

3. Open the project folder

4. Modify WiFi and MQTT configurations as needed (`src/main.cpp`):
   ```cpp
   // WiFi Configuration
   const char* ssid = "Your_WiFi_SSID";
   const char* password = "Your_WiFi_Password";
   
   // MQTT Configuration
   const char* mqtt_server = "broker.emqx.io";
   const int mqtt_port = 1883;
   ```

5. Compile and upload the code to ESP8266 development board

### Using Arduino IDE

1. Get sample code from `Docs/ArduinoSampleCode` directory

2. Open Arduino IDE and install ESP8266 board support

3. Install the required libraries: ESP8266WiFi, PubSubClient

4. Open `ESP8266_X32_TEST.ino` file

5. Modify WiFi and MQTT configurations as needed

6. Compile and upload the code to ESP8266 development board

## Usage Instructions

### MQTT Control Commands

Send commands in the following format to the topic `relay/control` via MQTT client:

- Turn on relay: `on_X` (X is relay number, 1-32)
  Example: `on_1` - Turn on relay 1

- Turn off relay: `off_X` (X is relay number, 1-32)
  Example: `off_1` - Turn off relay 1

### Recommended MQTT Clients

It is recommended to use [MQTTX](https://mqttx.app/downloads) as the MQTT client for testing and control.

## Project Structure

```
260113_ESP8266_32Relay/
├── .gitignore          # Git ignore file configuration
├── Docs/               # Project documentation
│   ├── ArduinoSampleCode/  # Arduino IDE compatible sample code
│   └── EN/             # English documentation
├── include/            # Header files directory
├── lib/                # Libraries directory
├── platformio.ini      # PlatformIO配置文件
├── src/                # Source code directory
│   └── main.cpp        # Main program file
└── test/               # Test directory
```

## Pin Definitions

| Function | ESP8266 Pin |
|------|-------------|
| HC595_SI (Data) | D5 (GPIO14) |
| HC595_SCK (Clock) | D7 (GPIO13) |
| HC595_RCK (Latch) | D6 (GPIO12) |
| HC595_G (Enable) | D1 (GPIO5) |

## Sample Code

### Turn on Relay 1

```cpp
RelayON(1);
```

### Turn off Relay 1

```cpp
RelayOFF(1);
```

### Cycle Control All Relays

```cpp
for (int i = 1; i <= 32; i++) {
  RelayON(i);
  delay(100);
}

for (int i = 1; i <= 32; i++) {
  RelayOFF(i);
  delay(100);
}
```

## Documentation

- `Docs/EN/`: Contains English documentation related to ESP8266
- `Docs/ArduinoSampleCode/`: Arduino IDE compatible sample code

## License

This project is licensed under the MIT License.

## Contact Information

If you have any questions or suggestions, please contact us through the following methods:

- Email: xuetao@newimagery.net
- https://github.com/newimagery/260113_ESP8266_32Relay
- WhatsAPP:+86 18601106543