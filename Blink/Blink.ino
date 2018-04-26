void setup() {
  //initialize LED pin
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  //initialize serial
  Serial.begin(9600);
}

void loop() {
  delay(1000);
  digitalWrite(2, LOW); //turn LED off
  delay(1000);
  digitalWrite(2, HIGH); //turn LED on
  
  Serial.println("Blink"); 

}
