#include <Arduino.h>
#include "WiFi.h"
#include "PubSubClient.h"
#include "Ticker.h"

const char *ssid = "oudafa";                 //wifi名
const char *password = "00000000";         //wifi密码
const char *mqtt_server = "183.230.40.39"; //onenet 的 IP地址

#define mqtt_devid "1044280970"  //设备ID
#define mqtt_pubid "571171"     //产品ID
#define mqtt_password "test123" //鉴权信息

WiFiClient espClient;           //创建一个WIFI连接客户端
PubSubClient client(espClient); // 创建一个PubSub客户端, 传入创建的WIFI客户端

char msg_buf[200];                                //发送信息缓冲区
char dataTemplate[] = "{\"temp\":%.2f,\"hum\":%.2f}"; //信息模板
char msgJson[75];                                 //要发送的json格式的数据
unsigned short json_len = 0;                      //json长度
Ticker tim1;                                      //定时器,用来循环上传数据

//连接WIFI相关函数
void setupWifi()
{
  delay(10);
  Serial.println("连接WIFI");
  WiFi.begin(ssid, password);
  while (!WiFi.isConnected())
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("OK");
  Serial.println("Wifi连接成功");
}

//收到主题下发的回调, 注意这个回调要实现三个形参 1:topic 主题, 2: payload: 传递过来的信息 3: length: 长度
void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.println("message rev:");
  Serial.println(topic);
  for (size_t i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  if (payload[0] == 49)
  {
    digitalWrite(2, HIGH);
  }
  if (payload[0] == 48)
  {
    digitalWrite(2, LOW);
  }

}

//向主题发送模拟的温湿度数据
void sendTempAndHumi()
{
  if (client.connected())
  {
    snprintf(msgJson, 40, dataTemplate, 22.31, 25.92); //将模拟温湿度数据套入dataTemplate模板中, 生成的字符串传给msgJson
    json_len = strlen(msgJson);                   //msgJson的长度
    msg_buf[0] = char(0x03);                       //要发送的数据必须按照ONENET的要求发送, 根据要求,数据第一位是3
    msg_buf[1] = char(json_len >> 8);              //数据第二位是要发送的数据长度的高八位
    msg_buf[2] = char(json_len & 0xff);            //数据第三位是要发送数据的长度的低八位
    memcpy(msg_buf + 3, msgJson, strlen(msgJson)); //从msg_buf的第四位开始,放入要传的数据msgJson
    msg_buf[3 + strlen(msgJson)] = 0;              //添加一个0作为最后一位, 这样要发送的msg_buf准备好了
    Serial.print("public message:");
    Serial.println(msgJson);
    client.publish("$dp", (uint8_t *)msg_buf, 3 + strlen(msgJson)); //发送数据到主题$dp
  }
}

//重连函数, 如果客户端断线,可以通过此函数重连
void clientReconnect()
{
  while (!client.connected()) //再重连客户端
  {
    Serial.println("reconnect MQTT...");
    if (client.connect(mqtt_devid, mqtt_pubid, mqtt_password))
    {
      Serial.println("connected");
    }
    else
    {
      Serial.println("failed");
      Serial.println(client.state());
      Serial.println("try again in 5 sec");
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(115200);                                  //初始化串口
  pinMode(2,OUTPUT);
  delay(3000);                                           //这个延时是为了让我打开串口助手
  setupWifi();                                           //调用函数连接WIFI
  client.setServer(mqtt_server, 6002);                   //设置客户端连接的服务器,连接Onenet服务器, 使用6002端口
  client.connect(mqtt_devid, mqtt_pubid, mqtt_password); //客户端连接到指定的产品的指定设备.同时输入鉴权信息
  client.setCallback(callback);                          //设置好客户端收到信息是的回调
  tim1.attach(20, sendTempAndHumi);                      //定时每20秒调用一次发送数据函数sendTempAndHumi
}

void loop()
{
  if (!WiFi.isConnected()) //先看WIFI是否还在连接
  {
    setupWifi();
  }
  if (!client.connected()) //如果客户端没连接ONENET, 重新连接
  {
    clientReconnect();
  }
  client.loop(); //客户端循环检测
}
