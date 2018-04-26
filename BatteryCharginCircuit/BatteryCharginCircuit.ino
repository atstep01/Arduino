//Voltage tester global variables
const float voltageDelay = 5000.0;
float lastCheckedVoltageTime = 0.0;

//Battery tester global variables
int reading = 0;
int relayPin = 7;
float voltage = 0.0;

void setup() {
//Battery tester setup
pinMode(A0,INPUT);
pinMode(relayPin,OUTPUT);
digitalWrite(relayPin,LOW);
//End battery tester setup

Serial.begin(9600);
 
}

void loop() {
 //Should only run voltageDelay milliseconds after last check
 if((millis() > voltageDelay + lastCheckedVoltageTime) || lastCheckedVoltageTime == 0.0)
 {
  digitalWrite(relayPin,HIGH);

  delay(100);

  reading = analogRead(A0);
  voltage = float(reading) * 2 * (5.0/1023.0);

  digitalWrite(relayPin,LOW);

  Serial.println(voltage);
  Serial.println(voltage,2);

  lastCheckedVoltageTime = millis();
 }
}
