#include "WiFi.h"
#include <TFT_eSPI.h>



const char *SSID = "";
const char *WiFiPassword = "";
void setup() {
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.fillScreen(TFT_BLACK);
  tft.setTextDatum(MC_DATUM);
  tft.setRotation(0);
  
  Serial.begin(115200);
  ConnectToWiFi();
  tft.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

}



void ConnectToWiFi(){
 
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, WiFiPassword);
  Serial.print("Connecting to "); Serial.println(SSID);
 
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(500);
 
    if ((++i % 16) == 0)
    {
      Serial.println(F(" still trying to connect"));
    }
  }
 
  Serial.print(F("Connected. My IP address is: "));
  Serial.println(WiFi.localIP());
}
