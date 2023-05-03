#include <Arduino.h>

int AUTO_TURN_OFF = 7;

int LED_RED = 6;
int LED_GREEN = 10;
int LED_BLUE = 5;

int IN_STATUS = 4;

void setup() {
  Serial.begin(115200);

  pinMode(AUTO_TURN_OFF, OUTPUT);
  digitalWrite(AUTO_TURN_OFF, HIGH);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  Serial.println("AUTO TURN OFF");
}

void loop() {
  digitalWrite(LED_RED, HIGH);
  digitalWrite(AUTO_TURN_OFF, HIGH);
  delay(5000);
  Serial.println("SLEEP");
  digitalWrite(LED_RED, LOW);
  digitalWrite(AUTO_TURN_OFF,LOW);
}