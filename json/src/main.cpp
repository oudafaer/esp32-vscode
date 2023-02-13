#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "ArduinoJson.h"

const char *ssid = "oudafa";
const char *pwd  = "00000000";

StaticJsonDocument<512> doc;


void setup() {
    Serial.begin(115200);
 
    //connect to WiFi
    Serial.printf("Connecting to %s ", ssid);
    WiFi.begin(ssid, pwd);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("Connected!");
 
    // local ip
    Serial.println(WiFi.localIP().toString());
 

}
 
void loop() {
      // HTTPClient init
    HTTPClient http;
    String url = "https://api.seniverse.com/v3/weather/now.json?key=SRJv6L_w-jaeG1AE1&location=jieyang&language=zh-Hans&unit=c";
    http.begin(url);
 
    // start get
    int http_code = http.GET();
 
    // handle http code
    if (http_code !=  HTTP_CODE_OK) {
        // get fail.
        Serial.printf("GET fail, http code is %s\n", http.errorToString(http_code).c_str());
        return;
    }
 
    // http response
    String response = http.getString();
// Stream& input;

    DeserializationError error = deserializeJson(doc, response);

    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return;
    }

    JsonObject results_0 = doc["results"][0];

    JsonObject results_0_location = results_0["location"];
    const char* results_0_location_id = results_0_location["id"]; // "WS4VBP4H9W1J"
    const char* results_0_location_name = results_0_location["name"]; // "揭阳"
    Serial.println(results_0_location_name);
    const char* results_0_location_country = results_0_location["country"]; // "CN"
    const char* results_0_location_path = results_0_location["path"]; // "揭阳,揭阳,广东,中国"
    const char* results_0_location_timezone = results_0_location["timezone"]; // "Asia/Shanghai"
    const char* results_0_location_timezone_offset = results_0_location["timezone_offset"]; // "+08:00"


    JsonObject results_0_now = results_0["now"];
    const char* results_0_now_text = results_0_now["text"]; // "阴"
    Serial.println(results_0_now_text);
    const char* results_0_now_code = results_0_now["code"]; // "9"
    const char* results_0_now_temperature = results_0_now["temperature"]; // "21"
    Serial.println(results_0_now_temperature);
    const char* results_0_last_update = results_0["last_update"]; // "2023-02-08T16:00:08+08:00"
    Serial.println(results_0_last_update);


 
    // close http
    http.end();
    delay(1000);
}