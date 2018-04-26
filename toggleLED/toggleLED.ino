String arduinoInput;

void setup() {
 pinMode(2, OUTPUT);
 Serial.begin(9600);
}

void loop() {
  if(Serial.available())
  {
    arduinoInput = Serial.readString();

    if(arduinoInput.equalsIgnoreCase("ON"))
    {
      Serial.println("Turning LED ON...");
      digitalWrite(2, HIGH);
    }
    else if(arduinoInput.equalsIgnoreCase("OFF"))
    {
      Serial.println("Turning LED OFF...");
      digitalWrite(2, LOW);
    }
    else
    {
      Serial.println("Unknown command!");
    }
  }

}
