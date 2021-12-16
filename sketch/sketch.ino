// Import required libraries
#include "WiFi.h"
#include <HTTPSServer.hpp>
#include <SSLCert.hpp>
#include <HTTPRequest.hpp>
#include <HTTPResponse.hpp>
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include <M5Core2.h>
#include "AsyncTCP.h"

using namespace httpsserver;
//the network that the board will be connected to
const char* ssid = "lmao";
const char* password = "12345678910";
// Create AsyncWebServer object on port 80
AsyncWebServer server (80);
SSLCert*cert;
HTTPSServer * secureServer;

void setup(){
  M5.begin(); //Init M5Core2.
  M5.Lcd.fillscreen(RED); //Set the screen color to red. 
  M5.Lcd.setCursor(10, 10); //Move the cursor position to (x, y).
  M5.Lcd.setTexcolor(WHITE); //Set the font color to white.
  M5.Lcd.setTextSize(10); // Set the font size.
  M5.Lcd.printf("Starting server"); //Serial output format string. 
