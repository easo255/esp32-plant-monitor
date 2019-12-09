#include "WiFi.h"
#include <TFT_eSPI.h>
#include "xbm.h"
#include <Button2.h>

#define BUTTON_2        0
#define BUTTON_1        35
int statusShown = false;

const char *SSID = "";
const char *WiFiPassword = "";
TFT_eSPI tft = TFT_eSPI(135, 240); 
Button2 btn1(BUTTON_1);
Button2 btn2(BUTTON_2);



void button_init()
{

    btn2.setPressedHandler([](Button2 & b) {
        Serial.println("button pressed");
        Serial.println(statusShown);
        showStatus();
    });

    btn1.setPressedHandler([](Button2 & b){
      Serial.println("button 2 pressed");
      showHomeScreen();
    });
  
}


void setup() {
  tft.fillScreen(TFT_BLACK);
  button_init();
  Serial.begin(115200);
  tft.init();
  showHomeScreen();

}

void loop() {
 button_loop();
}

void button_loop(){
  btn1.loop();
  btn2.loop();
  
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


void showStatus(){
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.setTextDatum(MC_DATUM);

 
  
 int x = 0;
 int y = 50;

  tft.setTextSize(10);
  tft.setRotation(1);
  tft.drawString(":)",  tft.width() / 2, tft.height() / 2 );
}

void showHomeScreen(){
  tft.setTextSize(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.setRotation(0);
  tft.drawString("Press right button for status",0,0);
  tft.drawString("status",0,10);

}
