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
const char* ssid = "lmao"; //change this to your ssid
const char* password = "12345678910"; //change this to your password
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
  //check if SPIFFS is working correctly
   Serial.begin(115200);
   if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");  
    return;
  }
  Serial.println("Creating certificate...");
   
  cert = new SSLCert();
 
  int createCertResult = createSelfSignedCert(
    *cert,
    KEYSIZE_2048,
    "CN=myesp.local,O=acme,C=US");
   
  if (createCertResult != 0) {
    Serial.printf("Error generating certificate");
    return; 
  }
 
  Serial.println("Certificate created with success");
   
  secureServer = new HTTPSServer(cert);
 
  
  
 
  
  
    ResourceNode * nodeRoot = new ResourceNode("/", "GET", [](HTTPRequest * req, HTTPResponse * res){
  });
 
  secureServer->registerNode(nodeRoot);
 
  secureServer->start();
   
  if (secureServer->isRunning()) {
    Serial.println("Server ready.");
    M5.Lcd.fillScreen(GREEN); //Set the screen color to green.
  M5.Lcd.setCursor(10, 10); //Move the cursor position to (x,y). 
  M5.Lcd.setTextColor(WHITE); //Set the font color to white.
  M5.Lcd.setTextSize(10);  //Set the font size.
  M5.Lcd.printf("Server ready");  //Serial output format string.
    
  }
 // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });

  // Route to load p5.dom.min.js file
  server.on("/p5.dom.min.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/p5.dom.min.js", "text/javascript");
  });

    // Route to load p5.min.js file
  server.on("/p5.min.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/p5.min.js", "text/javascript");
  });
      // Route to load sketch.js file
  server.on("/sketch.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/sketch.js", "text/javascript");
  });

  server.on("/ml5.min.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/ml5.min.js", "text/javascript");
  });
  //run server after all files are uploaded
server.begin();
}

void loop() {
  
}
