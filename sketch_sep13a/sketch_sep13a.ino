const int buttonPlus = 2;     // the number of the pushbutton pin
const int buttonMinus = 3;

// variables will change:
int buttonPlusState = 0;         // variable for reading the pushbutton status
int buttonMinusState = 0;
int pressedCounter = 0;
int lastPlusButtonState = 0;
int lastMinusButtonState = 0;

void setup() {
  pinMode(buttonPlus, INPUT);
  pinMode(buttonMinus, INPUT);
  Serial.begin(9600);
}

void loop() {

  buttonPlusState = digitalRead(buttonPlus);
  buttonMinusState = digitalRead(buttonMinus);
  
  if (buttonPlusState != lastPlusButtonState || buttonMinusState != lastMinusButtonState) {
    if (buttonPlusState == HIGH) {
      pressedCounter++;
      Serial.println(pressedCounter);
    }
    if (buttonMinusState == HIGH) {
      pressedCounter--;
      Serial.println(pressedCounter);
    }
    delay(50);
  }
  lastMinusButtonState = buttonMinusState;
  lastPlusButtonState = buttonPlusState;
}
