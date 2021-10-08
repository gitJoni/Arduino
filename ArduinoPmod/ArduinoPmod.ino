/************************************************************************
  Test of the Pmod MIC3
*************************************************************************
  Description: Pmod_MIC3
  The sound captured by the module is displayed in the serial plotter.
  You can set the sensitivity of the mic with the potentiometer (srewdriver might be needed).
  Material
  1. Arduino Uno
  2. Pmod MIC3
  Wiring
  Module<----------> Arduino
  VCC     to        5V
  GND     to        GND
  SCK     to        13 (SCK)
  MISO    to        12 (MISO)
  SS      to        10
************************************************************************/

#define SS 8 // Assignment of the SS pin MIC sensor
#define CS 6 // Assignment of the CS pin ALS sensor

#include <SPI.h> // call library
#include <WiFi101.h>
#include <PubSubClient.h>
#include <credentials.h>
#include <ArduinoJson.h>

char ssid[] = SECRET_SSID;
char passwd[] = SECRET_PSW;
const char* brokerUser = "use-token-auth";
const char* brokerPass = ")9ddw&ICbA)!Ps+(_*";
const char* broker = "ypessw.messaging.internetofthings.ibmcloud.com";

WiFiClient espClient;
PubSubClient client(espClient);

WiFiServer server(80);

void setup() {
  SPI.begin(); // initialization of SPI port
  SPI.setDataMode(SPI_MODE0); // configuration of SPI communication in mode 0
  SPI.setClockDivider(SPI_CLOCK_DIV16); // configuration of clock at 1MHz
  pinMode(SS, OUTPUT);
  connectToWifi();
  client.setServer(broker, 1883);
}

int data, volume;
DynamicJsonDocument doc(1024);
String output;
char testi[40];

void loop() {
  for (int i = 0; i < 50000; i++) {  // Creating average of 100 samples
    volume += MIC3_getSound();
    data += ALS_getData();
  }
  volume = volume / 50000;
  data = data / 50000;
  doc["volume"] = volume;
  doc["als"] = data;
  if (WiFi.status() != WL_CONNECTED) {
    connectToWifi();
  }
  if (!client.connected()){
    reconnect();
  }
  serializeJson(doc, testi);
  client.publish("iot-2/evt/1/fmt/json", testi);
}

void connectToWifi() {
  WiFi.begin(ssid, passwd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000); 
  }
}

void(* resetFunc) (void) = 0; // declare reset function @ address 0

void reconnect() {
  while (!client.connected()){
    if (client.connect("d:ypessw:Arduino:1212", brokerUser, brokerPass)) {
      // continue
    } else {
      resetFunc(); // If can't connect to cloud, this will reset the arduino.
    }
  }
}

int MIC3_getSound(void) {
  digitalWrite(SS, LOW);  //activate chip select
  int sound = SPI.transfer(0) | (SPI.transfer(0) << 8); //reconstruct 12-bit data
  digitalWrite(SS, HIGH); //deactivate chip select
  return sound;
}

int ALS_getData(void) {
  digitalWrite(CS, LOW);  //activate chip select
  int data = SPI.transfer(0) | (SPI.transfer(0) << 8); //reconstruct 12-bit data
  digitalWrite(CS, HIGH); //deactivate chip select
  return data;
}
