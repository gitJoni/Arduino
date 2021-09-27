#include "SevSeg.h"
SevSeg sevseg; //Initiate a seven segment controller object

void setup() {
    pinMode(A15, INPUT);
    pinMode(2, OUTPUT);
    byte numDigits = 4;  
    byte digitPins[] = {25, 24, 23, 22};
    byte segmentPins[] = {32, 31, 27, 29, 30, 26, 33, 28};
    bool resistorsOnSegments = 0; 
    // variable above indicates that 4 resistors were placed on the digit pins.
    // set variable to 1 if you want to use 8 resistors on the segment pins.
    sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
    sevseg.setBrightness(90);
}
int number = 0;

void loop() {
    number = analogRead(A15) / 10;
    sevseg.setNumber(number);
    tone(2, number * 30);
    sevseg.refreshDisplay(); // Must run repeatedly
}
