const int buttonInputPin = 3;
const int ledOutputPin = 2;

void setup() {
 pinMode(buttonInputPin, INPUT);
 pinMode(ledOutputPin, OUTPUT);
 digitalWrite(ledOutputPin, LOW);

}

void loop() {
  int input = digitalRead(buttonInputPin);
  digitalWrite(ledOutputPin, input);

}
