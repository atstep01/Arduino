//Pin Labels
const int interruptPin = 2;

//Global variables
int breakCount = 0;
float long startTime = 0.0;
float long endTime = 0.0;
float rpm = 0.0;
int numberOfBlades = 4;
float minutes = 0.0;

void setup() {
 //Initialize the serial interface
  Serial.begin(9600);
  //set interruptPin to input
  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), broken, FALLING);
}

void loop() {
 if(breakCount >= 30)
 {

  endTime = millis();
  //there are 60000 milliseconds in one minute and a full rotation is 4 break counts.
  minutes = (endTime - startTime) / 60000;
  rpm = (breakCount / numberOfBlades) / minutes;

  Serial.print("RPM = ");
  Serial.println(rpm);
  breakCount = 0;
 }
}

void broken ()
{
  if(breakCount == 0)
  {
    startTime = millis();
  }

  breakCount++;

}

