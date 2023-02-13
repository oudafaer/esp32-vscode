#include "Arduino.h"
#include "Ticker.h"

Ticker t1;
Ticker t2;

void func1()
{
  Serial.println("我是t1的回调,我没参数");
}
void func1(int a)
{
  Serial.print("我是t2的回调,我的参数是:");
  Serial.println(a);
}

void setup()
{
  Serial.begin(115200);
  if (1)
  {
    t1.once(10, func1);
    t2.once(20, func1, 8);
    //t1 t2 方法名都叫func1, 但其实是不同的方法, 这涉及到一个方法重载的概念
  }
}

void loop()
{
  Serial.println("我来证明我没被阻塞,也没法阻塞Ticker");
  delay(2700);
}
