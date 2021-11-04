#include <Arduino.h>
#include <WiFiManager.h>
#include <ESP8266WiFi.h>

//time libary
#include <ezTime.h>
Timezone Europe;

//display libary
#include <TM1637Display.h>
// Module connection pins (Digital Pins)
#define CLK D2
#define DIO D3
TM1637Display display(CLK, DIO);
int b = 0; //integer for the hours and minutes
int i = 0; //integer for seconds used to blink dots

//this is for showing COnF on Display while you haven´t configured wifi
const uint8_t CONF[] = {
	SEG_A | SEG_D | SEG_E | SEG_F,                   // C
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
	SEG_C | SEG_E | SEG_G,                           // n
	SEG_A | SEG_E | SEG_F | SEG_G                    // F
	};


void setup() {
	Serial.begin(9600);
  
  display.setBrightness(7, true);
  display.setSegments(CONF);
  
  //The Wifimagic
  WiFiManager wifiManager;
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  WiFiManager wm;
  bool res;
  res = wm.autoConnect("AutoConnectAP","password"); // password protected ap
  
  //some otherstuff for the time
  waitForSync();
  Europe.setLocation("Europe/Berlin");
	
}

void loop() {
  //This displays the current time
  String t = Europe.dateTime("hi"); //for simplicity I just used H for hours and i for minutes and no space so we get the time like 1200 instead of 12:00
  b = (int) t.toInt(); //Because the functions cannot handle strings
  String c = Europe.dateTime("s");
  i = (int) c.toInt(); //Because the functions cannot handle strings
    if ( (i % 2) == 0) { //show dots when seconds are even
        display.showNumberDecEx(b,0b01000000,true,4,0);
      
   }
    else {               //hide dots when seconds are uneven
        display.showNumberDecEx(b,0,true,4,0);
    }

 }