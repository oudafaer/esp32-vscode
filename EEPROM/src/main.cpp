#include <Arduino.h>
#include <EEPROM.h>

bool flag = false;

void setup()
{
  Serial.begin(115200);
  EEPROM.begin(4096);
}

void loop()
{
  if (Serial.available())
  {
    char temp = Serial.read();
    if (temp != 'x')
    {
      EEPROM.write(1, temp);
      EEPROM.commit();
      Serial.print("写入EEPROM:");
      Serial.println(EEPROM.read(1));
    }
    else
    {
      Serial.print("EEPROM里的数据是:");
      Serial.println(EEPROM.read(1));
    }
  }
}
