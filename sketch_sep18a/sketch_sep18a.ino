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
#include <credentials.h>
#include <ArduinoJson.h>

char ssid[] = SECRET_SSID;
char passwd[] = SECRET_PSW;

int status = WL_IDLE_STATUS;

WiFiServer server(80);

void setup() {
  Serial.begin(9600); // initialization of serial communication
  SPI.begin(); // initialization of SPI port
  SPI.setDataMode(SPI_MODE0); // configuration of SPI communication in mode 0
  SPI.setClockDivider(SPI_CLOCK_DIV16); // configuration of clock at 1MHz
  pinMode(SS, OUTPUT);
  while (!Serial) {
    ;
  }
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present, not continuing");
    while (true);
  }
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WiFi network.");
    status = WiFi.begin(ssid, passwd);
    delay(10000); 
  }
  server.begin();
  printWiFiStatus();
}

int data, volume;
DynamicJsonDocument doc(1024);

void loop() {
  volume = MIC3_getSound();
  data = ALS_getData();
  doc["volume"] = volume;
  doc["als"] = data;
  Serial.print(volume);
  Serial.print(" : ");
  Serial.println(data);
  delay(40);
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

void printWiFiStatus() {
 
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
