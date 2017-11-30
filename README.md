# mqtt-sn-sockets
**mqtt-sn-sockets** implementing the SocketInterfaces for **MQTT-SN Gateways** and **MQTT-SN Clients**.
The Sockets are implemented for **transmission technologies** ([OSI-Layer](https://en.wikipedia.org/wiki/OSI_model) [1](https://en.wikipedia.org/wiki/Physical_layer)) and **transmission protocols** ([OSI-Layer ](https://en.wikipedia.org/wiki/OSI_model)[2](https://en.wikipedia.org/wiki/OSI_model#Layer_2:_Data_Link_Layer), [3](https://en.wikipedia.org/wiki/OSI_model#Layer_3:_Network_Layer), [4](https://en.wikipedia.org/wiki/OSI_model#Layer_4:_Transport_Layer)).

#### Legend: 
* &#x2705; implemented and tested
* &#x274E; means not implemented yet - coming soon
* &#x274C; cannot implement it

## DummySocket
The DummySocket has no functionality.
It only prints out messages when calling functions.
Then you can see how the SocketInterface is to be implemented.
### Limitations
It has no functionality.

## ESP8266UDPSocket
The ESP8266UDPSocket implements the SocketInterface using [WiFi](https://en.wikipedia.org/wiki/Wi-Fi).
It uses [UDP](https://en.wikipedia.org/wiki/User_Datagram_Protocol) as transmission protocol.
### Supported Boards and other HW
Boards:
* [ESP8266](https://github.com/nodemcu/nodemcu-devkit-v1.0#nodemcu-devkit-v10) &#x2705;
* [ESP32](https://github.com/espressif/arduino-esp32#esp32dev-board-pinmap) &#x274E;
### Limitations
**None** - the ESP8266UDPSocket can join Multicast groups.
Works only on ESP8266-Chip.

## EthernetUDPSocket
The EthernetUDPSocket implements the SocketInterface using [Ethernet](https://en.wikipedia.org/wiki/Ethernet).
It uses [UDP](https://en.wikipedia.org/wiki/User_Datagram_Protocol) as transmission protocol.
### Supported Boards and other HW
Boards:
* [Arduino Uno](https://store.arduino.cc/arduino-uno-rev3) &#x2705;
* [Arduino Mega](https://store.arduino.cc/arduino-mega-2560-rev3) &#x2705;
* [Arduino Nano](https://store.arduino.cc/arduino-nano) &#x274C; (not possible - power consumption too high)
* [ESP8266](https://github.com/nodemcu/nodemcu-devkit-v1.0#nodemcu-devkit-v10) &#x274C; (could not make it work - see Limitations)
* [ESP32](https://github.com/espressif/arduino-esp32#esp32dev-board-pinmap) &#x274E;

Shield:
* [Arduino Ethernet Shield V1](https://www.arduino.cc/en/Main/ArduinoEthernetShieldV1) (implemented)

### Limitations
The EthernetUDPSocket cannot receive Multicast UDP Packet due to the Arduino's Ethernet Library.
It does not work on ESP8266 because the connection to the Ethernet Shield is not stable see [ESP8266 Issue#962](https://github.com/esp8266/Arduino/issues/962).

## NRF24Socket
The EthernetUDPSocket implements the SocketInterface using the [nRF24L01 modules](https://www.nordicsemi.com/eng/Products/2.4GHz-RF/nRF24L01P).
It uses [RHDatagrams](http://www.airspayce.com/mikem/arduino/RadioHead/classRHDatagram.html) as transmission protocol.
### Supported Boards and other HW
Boards:
* [Arduino Uno](https://store.arduino.cc/arduino-uno-rev3) &#x2705;
* [Arduino Mega](https://store.arduino.cc/arduino-mega-2560-rev3) &#x2705;
* [Arduino Nano](https://store.arduino.cc/arduino-nano) &#x2705;
* [ESP8266](https://github.com/nodemcu/nodemcu-devkit-v1.0#nodemcu-devkit-v10) &#x2705;
* [ESP32](https://github.com/espressif/arduino-esp32#esp32dev-board-pinmap) &#x274E;

Module:
* [nRF24L01+PCB](images/nRF24L01+PCB.jpg) &#x2705;
* [nRF24L01+PA+LNA](images/nRF24L01+PA+LNA.jpg) (I do not own them - not tested)

### Limitations
The nRF24L01 modules need a 3.3V power supply so you need to drop down the voltage to 3.3V if you use 5V.
Fortunately the other pins are 5V tolerant.
We send the messages without acknowledges so it is not said that the messages always reach their destination.

The modules drain a lot of energy during startup.
Soldering a 100uF capacitor between GND and VCC Pin on the modules solves this problem.

The NRF24Socket uses the RadioHead Library so your project is under the GPLv2 licence too.

## RF69Socket
The RF69Socket implements the SocketInterface using [LoRa](https://www.lora-alliance.org/).
It uses [RHDatagrams](http://www.airspayce.com/mikem/arduino/RadioHead/classRHDatagram.html) as transmission protocol.
### Supported Boards and other HW
Boards:
* [Arduino Uno](https://store.arduino.cc/arduino-uno-rev3) &#x2705;
* [Arduino Mega](https://store.arduino.cc/arduino-mega-2560-rev3) &#x274E;
* [Arduino Nano](https://store.arduino.cc/arduino-nano) &#x274E;
* [ESP8266](https://github.com/nodemcu/nodemcu-devkit-v1.0#nodemcu-devkit-v10) &#x274E;
* [ESP32](https://github.com/espressif/arduino-esp32#esp32dev-board-pinmap) &#x274E;
* [Adafruit Feather LoRa](https://www.adafruit.com/product/3078) &#x274E;

Module:
* [LoRa Shield](http://wiki.dragino.com/index.php?title=Lora_Shield) &#x274E;
* [LoRa/GPS Shield](http://wiki.dragino.com/index.php?title=Lora/GPS_Shield) &#x274E;
* [LoRra Bee](http://wiki.dragino.com/index.php?title=Lora_BEE) &#x274E;

### Limitations
The datarate of LoRa is very low and until now it is untested how good it works with MQTT-SN.

The RF69Socket uses the RadioHead Library so your project is under the GPLv2 licence too.


## BLESocket
The BLESocket implements the SocketInterface using [Bluetooth LE](https://en.wikipedia.org/wiki/Bluetooth_Low_Energy).
It uses [GATT operations](https://en.wikipedia.org/wiki/Bluetooth_Low_Energy#GATT_Operations) the UUID of the [Nordic Uart Service (NUS)](https://devzone.nordicsemi.com/documentation/nrf51/6.0.0/s110/html/a00066.html) as transmission protocol.
### Supported Boards and other HW
Boards:
* [ESP32](https://github.com/espressif/arduino-esp32#esp32dev-board-pinmap) &#x274E;

### Limitations
Works only on ESP-Chips.


# Examples
In the examples directory you can find ping-ping example.
These examples are for testing only and the different parts of the MQTT-SN Gateway/Client is implemented to print out received messages and send the payload back to the sender.
Each example contains a project you can load on a platform board and edit the define (PING or PONG).
The Ping then send at startup a message to Pong. Pong sends the message back. Basically the Ping starts a message containing {5, 'P', 'i', 'n', 'g'} which will travel between Ping and Pong.
The different parts of the MQTT-SN Gateway/Client is implemented to print out received messages and send the payload back to the sender.


# Example Project
If you have example projects using my Implementation send me a link or create a Issue.


# Licence
If not other mentioned in a file the MIT Licence is applied. For files mentioned otherwise the licence directoly mentioned in the file is applied.
## MIT
Copyright 2017 Gabriel Nikol

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## RadioHead
The [RadioHead Packet Radio library for embedded microprocessors](http://www.airspayce.com/mikem/arduino/RadioHead/) from airspayce is a great library to program a lot of wireless technologies.
We use [Version 1.81](http://www.airspayce.com/mikem/arduino/RadioHead/RadioHead-1.81.zip) downloaded from the official RadioHead side.
It is used for the NRF24Socket and the RF69Socket.
The library uses GPLv2 licence, so we use GPLv2 for our files using this library too.
Fortunately you can buy a commercial licence from the author if you want to use the library without GPLv2.
If you have such a commercial licence you are allowed to use our code under the MIT licence.
