void setup() 
{
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  pinMode(A5, INPUT);

}

void loop() 
{
  if(Serial.available())
  {
    String userInput = Serial.readString();

    if(userInput.equalsIgnoreCase("ON"))
    {
      digitalWrite(7, HIGH);
      Serial.println("Turning on...");
    }
    else if(userInput.equalsIgnoreCase("OFF"))
    {
      digitalWrite(7,LOW);
      Serial.println("Turning off...");
    }
  }

  int voltageDrop = analogRead(A5);
  if(voltageDrop > 0)
  {
    double Vr, I, P;
    double Vtotal = 5;
    Vr = (double)voltageDrop;
    Vr = Vr * Vtotal / 1024;
    I = Vr / 1;
    P = (Vtotal - Vr) * I;

    Serial.print(P);
    Serial.println("W");
  }

}
