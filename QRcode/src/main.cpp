#include <Arduino.h>
#include "SSD1306.h"
#include "qrcode.h"

SSD1306 display(0x3c, 21, 22);
QRcode qrcode(&display);

void setup()
{
  Serial.begin(115200);
  delay(5000);
  Serial.println("");
  Serial.println("Starting...");

  display.init();
  display.clear();
  display.display();

  qrcode.init();
  // create qrcode
  qrcode.create("<!DOCTYPE html><html><head><title>WIFI Config by lwang</title><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head><style type=\"text/css\">.input{display: block; margin-top: 10px;}.input span{width: 100px; float: left; float: left; height: 36px; line-height: 36px;}.input input{height: 30px;width: 200px;}.btn{width: 120px; height: 35px; background-color: #000000; border:0px; color:#ffffff; margin-top:15px; margin-left:100px;}</style><body><form method=\"GET\" action=\"connect\"><label class=\"input\"><span>WiFi SSID</span><input type=\"text\" name=\"ssid\"></label><label class=\"input\"><span>WiFi PASS</span><input type=\"text\"  name=\"pass\"></label><input class=\"btn\" type=\"submit\" name=\"submit\" value=\"Submie\"> <p><span> Nearby wifi:</P></form>");
}
void loop()
{

}

