#include <Arduino.h>
#include "driver/adc.h"
#include "Wire.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

int AUTO_TURN_OFF = 7;

int LED_RED = 6;
int LED_GREEN = 10;
int LED_BLUE = 5;

const char* broker = "";          
const char* mqttUsername = "";   
const char* mqttPassword = ""; 

WiFiClient espClient;
PubSubClient client(espClient);

// Connection host to IoT cloud
#define HOST "..."

// Connection port to IoT cloud
#define PORT 8883

// How often we send data to IoT cloud
#define PUBLISH_CYCLE 5000

// The device key to authenticate the device with IoT cloud
#define DEVICE_SECURITY_KEY ""

// The WiFi client, used to open TLS connections 
WiFiClientSecure netClient;

// An MQTT client to interpret and send MQTT packets
PubSubClient mqttClient(HOST, PORT, netClient);

const char* root_ca_cert = \
    "-----BEGIN CERTIFICATE-----\n" \
    "MIIFYDCCBEigAwIBAgIQQAF3ITfU6UK47naqPGQKtzANBgkqhkiG9w0BAQsFADA/\n" \
    "MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT\n" \
    "DkRTVCBSb290IENBIFgzMB4XDTIxMDEyMDE5MTQwM1oXDTI0MDkzMDE4MTQwM1ow\n" \
    "TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh\n" \
    "cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwggIiMA0GCSqGSIb3DQEB\n" \
    "AQUAA4ICDwAwggIKAoICAQCt6CRz9BQ385ueK1coHIe+3LffOJCMbjzmV6B493XC\n" \
    "ov71am72AE8o295ohmxEk7axY/0UEmu/H9LqMZshftEzPLpI9d1537O4/xLxIZpL\n" \
    "wYqGcWlKZmZsj348cL+tKSIG8+TA5oCu4kuPt5l+lAOf00eXfJlII1PoOK5PCm+D\n" \
    "LtFJV4yAdLbaL9A4jXsDcCEbdfIwPPqPrt3aY6vrFk/CjhFLfs8L6P+1dy70sntK\n" \
    "4EwSJQxwjQMpoOFTJOwT2e4ZvxCzSow/iaNhUd6shweU9GNx7C7ib1uYgeGJXDR5\n" \
    "bHbvO5BieebbpJovJsXQEOEO3tkQjhb7t/eo98flAgeYjzYIlefiN5YNNnWe+w5y\n" \
    "sR2bvAP5SQXYgd0FtCrWQemsAXaVCg/Y39W9Eh81LygXbNKYwagJZHduRze6zqxZ\n" \
    "Xmidf3LWicUGQSk+WT7dJvUkyRGnWqNMQB9GoZm1pzpRboY7nn1ypxIFeFntPlF4\n" \
    "FQsDj43QLwWyPntKHEtzBRL8xurgUBN8Q5N0s8p0544fAQjQMNRbcTa0B7rBMDBc\n" \
    "SLeCO5imfWCKoqMpgsy6vYMEG6KDA0Gh1gXxG8K28Kh8hjtGqEgqiNx2mna/H2ql\n" \
    "PRmP6zjzZN7IKw0KKP/32+IVQtQi0Cdd4Xn+GOdwiK1O5tmLOsbdJ1Fu/7xk9TND\n" \
    "TwIDAQABo4IBRjCCAUIwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMCAQYw\n" \
    "SwYIKwYBBQUHAQEEPzA9MDsGCCsGAQUFBzAChi9odHRwOi8vYXBwcy5pZGVudHJ1\n" \
    "c3QuY29tL3Jvb3RzL2RzdHJvb3RjYXgzLnA3YzAfBgNVHSMEGDAWgBTEp7Gkeyxx\n" \
    "+tvhS5B1/8QVYIWJEDBUBgNVHSAETTBLMAgGBmeBDAECATA/BgsrBgEEAYLfEwEB\n" \
    "ATAwMC4GCCsGAQUFBwIBFiJodHRwOi8vY3BzLnJvb3QteDEubGV0c2VuY3J5cHQu\n" \
    "b3JnMDwGA1UdHwQ1MDMwMaAvoC2GK2h0dHA6Ly9jcmwuaWRlbnRydXN0LmNvbS9E\n" \
    "U1RST09UQ0FYM0NSTC5jcmwwHQYDVR0OBBYEFHm0WeZ7tuXkAXOACIjIGlj26Ztu\n" \
    "MA0GCSqGSIb3DQEBCwUAA4IBAQAKcwBslm7/DlLQrt2M51oGrS+o44+/yQoDFVDC\n" \
    "5WxCu2+b9LRPwkSICHXM6webFGJueN7sJ7o5XPWioW5WlHAQU7G75K/QosMrAdSW\n" \
    "9MUgNTP52GE24HGNtLi1qoJFlcDyqSMo59ahy2cI2qBDLKobkx/J3vWraV0T9VuG\n" \
    "WCLKTVXkcGdtwlfFRjlBz4pYg1htmf5X6DYO8A4jqv2Il9DjXA6USbW1FzXSLr9O\n" \
    "he8Y4IWS6wY7bCkjCWDcRQJMEhg76fsO3txE+FiYruq9RUWhiF1myv4Q6W+CyBFC\n" \
    "Dfvp7OOGAN6dEOM4+qR9sdjoSYKEBpsr6GtPAQw4dy753ec5\n" \
    "-----END CERTIFICATE-----\n";

void connectWifi() {
    // Put the WiFi in station mode
    WiFi.mode(WIFI_STA);

    WiFi.begin("OBJ-A1", "4YN9yEXzdAGtDeKuQhA6USyZ");

    Serial.print("Connecting to WiFi...");

    // Wait for WiFi to connect
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);
    }

    Serial.println();
    Serial.print("WiFi connected.");
    Serial.println();

    // Set the CA certificate for validation
    netClient.setCACert(root_ca_cert);
}

void connectMqtt() {
    Serial.print("Connecting to MQTT...");
    while(!mqttClient.connect("OBJEX", "unused", DEVICE_SECURITY_KEY)) {
        Serial.print(".");
        delay(1000);
    }

    Serial.println();
    Serial.print("Connected to IoT cloud");
    Serial.println();
}

void setup() {
  pinMode(AUTO_TURN_OFF, OUTPUT);
  digitalWrite(AUTO_TURN_OFF, HIGH);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_2_5);

  // Set up the WiFi connection
  connectWifi();
  // Set up the connection to Beeno
  connectMqtt();
}

void loop() {
  // Update the status of the MQTT clients
    mqttClient.loop();

    // Check the WiFi status and reconnect if needed
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Disconnected from WiFi");
        connectWifi();
    }

    // Check the MQTT client status and reconnect if needed
    if (!mqttClient.connected()) {
        Serial.println("Disconnected from Beeno");
        connectMqtt();
    }

    // Create the JSON payload using the maximum available MQTT packet size.
    // The size of the document can be changed as needed
    StaticJsonDocument<MQTT_MAX_PACKET_SIZE> doc;
    JsonArray timeseries = doc.createNestedArray("timeseries");

    JsonObject tempObj = timeseries.createNestedObject();

    int IN_STATUS = adc1_get_raw((adc1_channel_t)4);

    if(IN_STATUS){
      tempObj["measurement"] = "status";
      tempObj["points"][0]["value"] = 1;
      digitalWrite(LED_RED, HIGH);
      digitalWrite(LED_GREEN, LOW);
    }else{
      tempObj["measurement"] = "status";
      tempObj["points"][0]["value"] = 0;
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, HIGH);
    }
    Serial.println("SLEEP");
    digitalWrite(LED_RED, LOW);
    digitalWrite(AUTO_TURN_OFF,LOW);
}