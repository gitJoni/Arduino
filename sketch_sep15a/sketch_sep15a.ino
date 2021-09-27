
const int ledit[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 22, 23};
const int ledit_length = sizeof(ledit) / sizeof(ledit[0]);

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < ledit_length; i++) {
    pinMode(ledit[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < ledit_length; i++) {
    digitalWrite(ledit[i], HIGH);
    delay(150);
  }
  for (int i = 0; i < ledit_length; i++) {
    digitalWrite(ledit[i], LOW);
    delay(150);
  }
  for (int i = ledit_length; i > -1; i--) {
    digitalWrite(ledit[i], HIGH);
    delay(150);
  }
  for (int i = ledit_length; i > -1; i--) {
    digitalWrite(ledit[i], LOW);
    delay(150);
  }
}
