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
- connected accordingly to the wiring diagram provided.
- reference [link](https://youtu.be/pJLjFm4Ipro?si=R0mi3gIHKcW8hYkH)

## Data generation in google sheets using appscript
- Create a Spreadsheet in google sheet.
- Create 3 sheets one for data entry(Inventory going IN/OUT), another one for temperature,humidity,etc stuff, Last one showing manipulated data from the first sheet, which update
  itself whenever the first sheeet is updating.
- **do note** the SpreadSheetID from the link shown in url bar at the top for ex: ("https://docs.google.com/spreadsheets/d/3DAcC1ekiehjSFaSDNk1JmukOC9fG-Y4tADqwi9kRdF8/edit?gid=811695338#gid=811695338")
  here the spreadsheetid is ("3DAcC1ekiehjSFaSDNk1JmukOC9fG-Y4tADqwi9kRdF8")

##  AppScript code
- under extensions > Apps Script
- now click + and select script like wise create another script too, one for getting inventory data(tablet pack details mfg, expiry, time, data) from ESP, publishing it in 1st sheet
- and another one for getting storage conditions fetched from ESP32 and publishing in 2nd sheet
- after deploying each script via deploy option, **do note** WEB APP URL link to make ESP32 use it to communicate its data to appscript->sheets 
- the code for each script is in [Appscript](https://github.com/Sanjay3184/IoT-Driven-Drug-Management-System/tree/main/AppScript)

## Coding Setup in Arduino IDE
- first thing is to write some data in your rfid tags for that refer <codefile>
- after having data in rfid tags deploy these two codes accordingly for entry side ESP32 and exit side ESP32 [ESP32 Codes](https://github.com/Sanjay3184/IoT-Driven-Drug-Management-System/tree/main/ESP32%20Codes) 
- now deploy two codes in each of the ESP accordingly from [ESP32 Codes](https://github.com/Sanjay3184/IoT-Driven-Drug-Management-System/tree/main/ESP32%20Codes)

## Finally Create a customized UI with AppSheet
- import sheets to use those data and create a graphical interface
- Layout of my Inventory Tracker app is in [Project Model Showcase](https://github.com/Sanjay3184/IoT-Driven-Drug-Management-System/tree/main/Project%20Model%20Showcase) refer
- do refer <[Appsheet yt channel](www.youtube.com/@AppSheetApps)>
