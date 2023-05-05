#include <Arduino.h>
#include "secrets.h"
#include "driver/adc.h"
#include "Wire.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"

int AUTO_TURN_OFF = 7;

int LED_RED = 6;
int LED_GREEN = 10;
int LED_BLUE = 5;

int doorStatus;

#define AWS_IOT_PUBLISH_TOPIC   "OBJEX_DW/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "OBJEX_DW/sub"

WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);


void messageHandler(char* topic, byte* payload, unsigned int length){
  Serial.print("incoming: ");
  Serial.println(topic);
 
  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  const char* message = doc["message"];
  Serial.println(message);
}

void connectAWS(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 
  Serial.println("Connecting to Wi-Fi");
 
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
 
  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);
 
  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.setServer(AWS_IOT_ENDPOINT, 8883);
 
  // Create a message handler
  client.setCallback(messageHandler);
 
  Serial.println("Connecting to AWS IOT");
 
  while(!client.connect(THINGNAME)){
    Serial.print(".");
    delay(100);
  }
 
  if(!client.connected()){
    Serial.println("AWS IoT Timeout!");
    return;
  }
  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
  Serial.println("AWS IoT Connected!");
}

void publishMessage(){
  StaticJsonDocument<200> doc;
  doc["DOOR"] = doorStatus;
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to client
 
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

void setup() {
  Serial.begin(115200);
  pinMode(AUTO_TURN_OFF, OUTPUT);
  digitalWrite(AUTO_TURN_OFF, HIGH);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_2_5);

  connectAWS();
}

void loop() {
    int IN_STATUS = adc1_get_raw((adc1_channel_t)4);

    if(IN_STATUS){
      doorStatus = 1;
      digitalWrite(LED_RED, HIGH);
      digitalWrite(LED_GREEN, LOW);
    }else{
      doorStatus = 0;
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, HIGH);
    }

    publishMessage();
    client.loop();

    Serial.println("SLEEP");
    digitalWrite(LED_RED, LOW);
    digitalWrite(AUTO_TURN_OFF,LOW);
}