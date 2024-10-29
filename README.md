# IoT-Drug-Management-System

## Components Used
- RFID reader (MFRC522) cheaper
- RFID tags read/writable
- DC FAN and relay to connect
- BreadBoard (63x10), Some jumper Wires(M-F,F-M)
- ESP32s
  
## First up hardware,Software Setup
- DHT sensor library (V1.3.5) : Install via "Manage Libraries" or "Library Manager" on the Arduino IDE, version number at the time of project it may not be the same currently.
- Ensure that you have the following libraries in your arduino IDE
  - WiFi.h
  - MFRC522 by github community
  - DHT sensor library by Adafruit 
- With help of Circuit Diagrams connect manually rfid with both ESP's
- One ESP have conection to DC FAN as well as DHT11 in my case to sense and operate DC FAN
- connected accordingly to the wiring diagram provided in <folder_name>

## Coding Setup in Arduino IDE
- first thing is to write some data in your rfid tags for that refer <codefile>
- now deploy two codes in each of the ESP from <ESP32 Codes>
