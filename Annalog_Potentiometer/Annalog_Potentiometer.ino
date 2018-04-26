const int inputPin = A0;

void setup() {
 Serial.begin(9600);
 pinMode(inputPin, INPUT);

}

void loop() {
  Serial.println(analogRead(inputPin));
}
