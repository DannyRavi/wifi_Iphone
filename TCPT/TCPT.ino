
/*
 * Copyright (c) 2018, circuits4you.com
 * All rights reserved.
 * Create a TCP Server on ESP8266 NodeMCU. 
 * TCP Socket Server Send Receive Demo copy2
*/
 
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
//#include "RTPPacket.h"
#define SendKey 0  //Button to send data Flash BTN on NodeMCU
#define SOFT_SERIAL_SPEED 115200  //should be match to target device
 
int port = 8888;  //Port number
WiFiServer server(port);

SoftwareSerial ss(D6,D5); // D6=rx , D5=tx

uint8_t buff[50];
//Server connect to WiFi Network
const char *ssid = "MobinNet0ECA";  //Enter your wifi SSID
const char *password = "EFFE0ECA";  //Enter your wifi Password
 
int count=0;
int data_soft_serial;
//=======================================================================
//                    Power on setup
//=======================================================================
void setup() 
{
  Serial.begin(115200);
  pinMode(SendKey,INPUT_PULLUP);  //Btn to send data
  Serial.println();
 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); //Connect to wifi
 
  // Wait for connection  
  Serial.println("Connecting to Wifi");
  while (WiFi.status() != WL_CONNECTED) {   
    delay(500);
    Serial.print(".");
    delay(500);
  }
 
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
 
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  
  server.begin();
  Serial.print("Open Telnet and connect to IP:");
  Serial.print(WiFi.localIP());
  Serial.print(" on port ");
  Serial.println(port);

  //soft Serial Setup _ should be the same as target device
  ss.begin(SOFT_SERIAL_SPEED);
  Serial.begin(SOFT_SERIAL_SPEED);
  //////////////////

}
//=======================================================================
//                    Loop
//=======================================================================
 
void loop() 
{
  WiFiClient client = server.available();
  char vol; // 8-bits data recieved from server (Volume)





  /*
  if (client) {
    if(client.connected())
    {
      Serial.println("Client Connected");
    }
    //int sensorValue = analogRead(A0);
    // Serial.print(sensorValue);
    while(client.connected()){      
      while(client.available()>0){
        // read data from the connected client
        //Serial.write(client.read());
         vol=client.read(); //recieve data from server
    */     if (ss.available()>0)
          {
            data_soft_serial=ss.write(vol); // send to DAC
            Serial.println(vol); // debug
          }
 /*     }
      //Send Data to connected client
      //// while(Serial.available()>0)
      //// {
      //  int sensorValue = analogRead(A0);
        int numberChar = 5;
       //// client.write((int)sensorValue);
      //! RTPPacket((uint8_t *)"Hello", 0, 0).serialize(buff);
      //! client.write(buff,50);
      client.write(numberChar);
      //// }
    }
    client.stop();
    Serial.println("Client disconnected");    
  }*/
}
