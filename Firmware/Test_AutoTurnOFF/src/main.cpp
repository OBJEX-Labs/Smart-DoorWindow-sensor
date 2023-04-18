#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  Serial.println("AUTO TURN ON");

}

void loop() {
  digitalWrite(7, HIGH);
  delay(5000);
  Serial.println("SLEEP");
  digitalWrite(7,LOW);
}