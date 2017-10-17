/**
 * BasicHTTPClient.ino
 *
 *  Created on: 24.05.2015
 *
 */

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

String SSID = "***";
String PASS = "***";
String SERVER = "192.168.***";

const bool DBG = false;
void setup() {
    if(DBG) {
      USE_SERIAL.begin(115200);
      USE_SERIAL.setDebugOutput(true);
  
      USE_SERIAL.println();
      USE_SERIAL.println();
      USE_SERIAL.println();
  
      for(uint8_t t = 4; t > 0; t--) {
          USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
          USE_SERIAL.flush();
          delay(1000);
      }
    }

    WiFiMulti.addAP(SSID.c_str(), PASS.c_str());

}

void loop() {
    // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        // configure traged server and url
        //http.begin("https://192.168.1.12/test.html", "7a 9c f4 db 40 d3 62 5a 6e 21 bc 5c cc 66 c8 3e a1 45 59 38"); //HTTPS
        String url = "http://" + SERVER + "/?from=esp";
        if (DBG) {
          USE_SERIAL.printf("[HTTP] begin...");
          USE_SERIAL.print(url);
        }
        
        http.begin(url.c_str()); //HTTP

        if (DBG) {
          USE_SERIAL.print("[HTTP] GET...\n");
        }
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
          
            if (DBG) {
              USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);
            }
            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                if (DBG) {
        
                  USE_SERIAL.println(payload);
                }
            }
        } else {
            
            if (DBG) {
              USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
            }
        }

        http.end();
    }

    delay(10000);
}

