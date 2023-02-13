#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char *ssid = "oudafa";    //你的网络名称
const char *password = "00000000"; //你的网络密码

void setup()
{
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected!");

  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  HTTPClient http; // 声明HTTPClient对象

  http.begin("http://api.bilibili.com/x/relation/stat?vmid=314597633"); // 准备启用连接

  int httpCode = http.GET(); // 发起GET请求

  if (httpCode > 0) // 如果状态码大于0说明请求过程无异常
  {
    if (httpCode == HTTP_CODE_OK) // 请求被服务器正常响应，等同于httpCode == 200
    {
      uint8_t buff[128] = {0};

      int len = http.getSize(); // 读取响应正文数据字节数，如果返回-1是因为响应头中没有Content-Length属性

      WiFiClient *stream = http.getStreamPtr(); // 获取响应正文数据流指针

      while (http.connected() && (len > 0 || len == -1)) // 当前已连接并且有数据可读
      {
        size_t size = stream->available(); // 获取数据流中可用字节数
        if (size)
        {
          int c = stream->readBytes(buff, ((size > sizeof(buff)) ? sizeof(buff) : size)); // 读取数据到buff

          Serial.write(buff, c);
          if (len > 0)
          {
            len -= c;
          }
        }
        delay(1);
      }
    }
  }
  else
  {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end(); // 结束当前连接

  delay(10000);
}
