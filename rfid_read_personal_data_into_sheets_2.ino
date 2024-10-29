//----------------------------------------Including the libraries.
#include "WiFi.h"
#include <HTTPClient.h>
#include <SPI.h>
#include <MFRC522.h>
#include "DHT.h"

#define RST_PIN         22
#define SS_PIN          5

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

//----------------------------------------SSID and PASSWORD of your WiFi network.
const char* ssid = "Subdid";  //--> Your wifi name
const char* password = "qwertyuiop"; //--> Your wifi password
//----------------------------------------

// Google script Web_App_URL.
String Web_App_URL = "https://script.google.com/macros/s/AKfycbzi28aTnXhTmMWfkSDwSfxmJYHVmuN__cJG5g1axGRrkOMD_-c-X7OK6EwGOL8Fr4iz/exec";

void setup() {

  Serial.begin(115200);
  Serial.println();

  SPI.begin();                                                  // Init SPI bus
  mfrc522.PCD_Init();                                              // Init MFRC522 card
  Serial.println(F("Read personal data on a MIFARE PICC:"));    //shows in serial that it is ready to read

  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

}

void loop() {

  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  //some variables we need
  byte block;
  byte len;
  MFRC522::StatusCode status;

  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.println(F("**Card Detected:**"));

  //-------------------------------------------

  mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); //dump some details about the card

  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));      //uncomment this to see all blocks in hex

  Serial.print(F("Name: "));

  byte buffer1[18];

  block = 4;
  len = 18;

  //------------------------------------------- GET FIRST NAME
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  String total1="";

  //PRINT FIRST NAME
  for (uint8_t i = 0; i < 16; i++)
  {
    if (buffer1[i] != 32)
    {
      total1 = total1 + String((char)buffer1[i]);
    }
  }

  String inputString = total1;
  String mfg, expr;

  int splitIndex = inputString.indexOf('/');
  if (splitIndex != -1) {
    mfg = inputString.substring(0, splitIndex);
    expr = inputString.substring(splitIndex + 1);
  } 
  else {
    Serial.println("Error: Delimiter not found.");
  }

  Serial.println("mfg: "+ mfg);
  Serial.println("expr: "+ expr);

  //---------------------------------------- GET LAST NAME

  byte buffer2[18];
  block = 1;

  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 1, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Read(block, buffer2, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  String medinf, med, mf, statusStr="OUT";

  //PRINT LAST NAME
  for (uint8_t i = 0; i < 16; i++) {
    //Serial.write(buffer2[i]);
    medinf = medinf+String((char)buffer2[i]) ;
  }
  Serial.print(medinf);

  Serial.println(F("\n**End Reading**\n"));

  delay(1000); //change value if you want to read cards faster

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();

  for( int i=0; i<medinf.length(); i++)
  {
    if( medinf[i]!=' ')
      med+=medinf[i];
  }

  for( int i=1; i<mfg.length(); i++)
    mf+=mfg[i];
  
  // Create a URL for sending or writing data to Google Sheets.
  String Send_Data_URL = Web_App_URL + "?sts=write";
  Send_Data_URL += "&medinf=" + med;
  Send_Data_URL += "&mfg=" + mf;
  Send_Data_URL += "&exp=" + expr;
  Send_Data_URL += "&sta=" + statusStr;

  Serial.print("-------------");
  Serial.println("Send data to Google Spreadsheet...");
  Serial.print("URL : ");
  Serial.println(Send_Data_URL);

  //::::::::::::::::::The process of sending or writing data to Google Sheets.
  // Initialize HTTPClient as "http".
  HTTPClient http;
  // HTTP GET Request.
  http.begin(Send_Data_URL.c_str());
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  
  // Gets the HTTP status code.
  int httpCode = http.GET(); 
  Serial.print("HTTP Status Code : ");
  Serial.println(httpCode);
  
  // Getting response from google sheets.
  String payload;
  if (httpCode > 0) {
    payload = http.getString();
    Serial.println("Payload : " + payload);    
  }
  http.end();

  delay(1000);

}