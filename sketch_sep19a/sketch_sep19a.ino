void setup() {
  // put your setup code here, to run once:
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(A4, HIGH);
  delay(500);
  digitalWrite(A4, LOW);
  delay(500);
  digitalWrite(A5, HIGH);
  delay(500);
  digitalWrite(A5, LOW);
  delay(500);
}
