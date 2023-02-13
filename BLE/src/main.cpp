#include <Arduino.h>
#include "WiFi.h"
 
const char *ssid = "ESP32AP";
const  char *password = "12345678";

void setup()
{
  Serial.begin(115200);
  WiFi.softAP(ssid,password);


}

void loop()
{

}   