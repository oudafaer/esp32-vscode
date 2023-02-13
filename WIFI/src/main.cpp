#include <Arduino.h>
#include "WiFi.h"
 
void mySmartWifiConfig()
{
  WiFi.mode(WIFI_MODE_STA);
  Serial.println("kai qi zhi neng pei wang:");
  WiFi.beginSmartConfig();
  while (1)
  {
    Serial.print(".");
    delay(500);
    if (WiFi.smartConfigDone())
    {
      Serial.println("pei wang cheng gong");
      Serial.printf("SSID:%s", WiFi.SSID().c_str());
      Serial.printf("PSW:%s", WiFi.psk().c_str());
      break;
    }
  }
}
 
bool autoConfig()
{
//  WiFi.disconnect(true,true);
  WiFi.begin();
  for (size_t i = 0; i < 20; i++)
  {
    int wifiStatus = WiFi.status();
    if (wifiStatus == WL_CONNECTED)
    {
      Serial.println("zi dong lian jie cheng gong!");
      return 1;
    }
    else
    {
      delay(1000);
      Serial.println("deng dai zi dong pei wang...");
    }
  }
  Serial.println("wufazidongpeiwang!");
  return 0;
}
 
void setup()
{
  Serial.begin(115200);
  delay(5000);
  if (!autoConfig())
  {
    mySmartWifiConfig();
  }
}
void loop()
{
  if (WiFi.isConnected())
  {
    Serial.println("wang luo yi lian jie");
    delay(1000);
  }
}