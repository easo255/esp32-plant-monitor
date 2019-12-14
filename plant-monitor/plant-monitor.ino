
#include "WiFi.h"
#include <TFT_eSPI.h>
#include "secrets.h"
#include <Button2.h>
#include <HTTPClient.h>

#define BUTTON_2        0
#define BUTTON_1        35
int statusShown = false;

const char *SSID = SECRET_SSID;
const char *WiFiPassword = SECRET_PASS;
TFT_eSPI tft = TFT_eSPI(135, 240); 
Button2 btn1(BUTTON_1);
Button2 btn2(BUTTON_2);
int moisture = 0;
boolean wifi = false;



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
  ConnectToWiFi();
  button_init();
  tft.fillScreen(TFT_BLACK);
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
  Serial.print("Connecting to "); 
  Serial.println(SSID);
 
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
  wifi = true;
}


void showStatus(){
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.setTextDatum(MC_DATUM);

 
  
 int x = 0;
 int y = 50;

  tft.setTextSize(10);
  tft.setRotation(1);
  moisture = analogRead(37);
  Serial.println(moisture);
  if(moisture > 3000){
    tft.drawString(":(",  tft.width() / 2, tft.height() / 2 );
    tft.setTextSize(1);
    tft.setRotation(0);
    tft.drawString("Fuktighet: " + String(moisture),  70,70 );

  }else{
    tft.drawString(":)",  tft.width() / 2, tft.height() / 2 );
    tft.setTextSize(1);
    tft.setRotation(0);
    tft.drawString("Fuktighet: " + String(moisture),  70,70 );
  }

  sendToFunction(moisture);

}

void showHomeScreen(){
  tft.setTextSize(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.setRotation(0);
  tft.drawString("Press right button for status",0,0);
  tft.drawString("status",0,10);
  tft.setTextDatum(MC_DATUM);
  tft.drawString("wifi: " + String(wifi),70,120);

  
}

void sendToFunction(int value){
   if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;   
 
    http.begin(URL+String(value));  //Specify destination for HTTP request
    http.addHeader("Content-Type", "text/plain; charset=utf-8");             //Specify content-type header
 
    int httpResponseCode = http.POST(String(value));   //Send the actual POST request
 
    Serial.println(httpResponseCode);   //Print return code

    


}
}
