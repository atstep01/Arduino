const int inputPin = A0;
const int ledOutputPin = 2;

void setup() {
 Serial.begin(9600);
 pinMode(inputPin, INPUT);
 pinMode(ledOutputPin, OUTPUT);
 digitalWrite(ledOutputPin, LOW);
 
}

void loop() {
  int arduinoInput = analogRead(inputPin);
  Serial.println(analogRead(inputPin));

    if(arduinoInput >= 500 )
    {
      digitalWrite(2, HIGH);
    }
    else if(arduinoInput < 500)
    {
      digitalWrite(2, LOW);
    }
}
