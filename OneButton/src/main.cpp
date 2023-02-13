#include <Arduino.h>
#include "OneButton.h"

#define PIN_INPUT 0
#define PIN_LED 2

OneButton button(PIN_INPUT, true);

void doubleclick()
{
  for (size_t i = 0; i < 4; i++)
  {
    digitalWrite(PIN_LED, !digitalRead(PIN_LED));
    delay(300);
  }
}
void click()
{
  Serial.println("click");
  for (size_t i = 0; i < 2; i++)
  {
    digitalWrite(PIN_LED, !digitalRead(PIN_LED));
    delay(100);
  }
}
void longclick()
{
  Serial.println("longclick");
  digitalWrite(PIN_LED, !digitalRead(PIN_LED));
  if (digitalRead(PIN_LED))
    Serial.println("start");
  else
    Serial.println("end");
}

void setup()
{
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);
  button.attachClick(click);
  button.attachDoubleClick(doubleclick);
  button.attachLongPressStart(longclick);
}
void loop()
{
  button.tick();
  delay(10);
}
