/*
 * Copyright (c) 2018, circuits4you.com
 * All rights reserved.
 * Create a TCP Server on ESP8266 NodeMCU. 
 * TCP Socket Server Send Receive Demo
*/
 
 
#include <ESP8266WiFi.h>
//#include "RTPPacket.h"
#define SendKey 0  //Button to send data Flash BTN on NodeMCU

int port = 8888;  //Port number
WiFiServer server(port);
uint8_t buff[50];
//Server connect to WiFi Network
const char *ssid = "MobinNet0ECA";  //Enter your wifi SSID
const char *password = "EFFE0ECA";  //Enter your wifi Password
 
int count=0;
int data_serial=0;
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



}
//=======================================================================
//                    Loop
//=======================================================================
 
void loop() 
{
  WiFiClient client = server.available();
 
  char digit[2]; // 2 digit recieve 
  char vol;
  int micValue=0;

  if (client) {
    if(client.connected())
    {
      Serial.println("Client Connected");
    }
    //int sensorValue = analogRead(A0);
    // Serial.print(sensorValue);
    while(client.connected()){      
      while(client.available()>1){
        // read data from the connected client
        //Serial.write(client.read());

        //////////////////////////
        // Serial.write(vol-48);  //  ASCII TO BINARY
        ///////////////////////////

        
         digit[1]=client.read()-48; //recieve data from server and convert ASCII to number 
         digit[0]=client.read()-48; // Yekaan //  convert ASCII to number 
         vol=digit[1]*10+digit[0];  //convert array to int
         //Serial.println(vol);
         Serial.write(vol);


       }
      //Send Data to connected client

         micValue=analogRead(A0);
         client.write(micValue);
         client.write(13);
      //// while(Serial.available()>0)
      //// {
      //  int sensorValue = analogRead(A0);
     //**   int numberChar = 5;
       //// client.write((int)sensorValue);
      //! RTPPacket((uint8_t *)"Hello", 0, 0).serialize(buff);
      //! client.write(buff,50);
      //**client.write(numberChar);
      //// }
    }
    client.stop();
    Serial.println("Client disconnected");    
  }
}

