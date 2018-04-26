#include <LiquidCrystal.h>
 // initializes LCD
  LiquidCrystal lcd(8,9,10,11,12,13);
  
  //Pin Labels
  const int interruptPin = 2; //Pin detects when blades interupt the tachometer.
  const int buttonPin = 3; //Pin detects when the button is pressed.
  

   //Global variables
   
   //rpm vairables
   // Initailizes break count and sets to 0, This counts the number of times the blades break the tachometer beam.
  int breakCount = 0; 
  float  startTime = 0.0; // This is the time we start
  float  endTime = 0.0; // This is the time we end
  int rpm = 0; // This is revolutions per minute. 
  int numberOfBlades = 4; // We have four fan blades.
  // This is mainly a conversion vairable, so we can get rpm in proper units.
  float minutes = 0.0; 
  
  //lcd variables
  int displaySetting = 1; //This is the display setting, determines which set of information is displayed on the LCD
  const int MAX_DISPLAYS = 3; // There are three possible screens for the button to toggle
  unsigned long lastDisplaySwitch = millis(); // takes the time of the last display
  const int DISPLAY_DELAY = 250; // delay of the lcd toggle

  //Efficiency and Power
  //Most of these vairables are just used in calculating the efficiency and power.
  double eff; // the efficiency
  int nIn; // rpm
  int nOut; // product of rpm and gear ratio
  double powerOut; // The power of the system
  double powerIn; // Power put into the system
  double powerInMotor; //Power the motor puts into the system
  double torqueIn; //Torque exerted on the system
  double torqueOut; //Torque exerted by the windmill
  double torqueOutGCM; //the torque out of the system in grams/cm
  int nMotor; // Efficiency of the motor
  int teethIn = 8; // Number of teeth on the motor 
  int teethOut = 16; // Number of teeth on the fan blade axle
  int gearRatio = teethOut / teethIn; // teeth out divided by teeth in 
  

void setup() {
  // lcd start
  lcd.begin(16,2);// initializes LCD
  lcd.display(); // LCD starts display

  //set interruptPin to input
  pinMode(interruptPin, INPUT); // sets interrupt pin to recieve input
  // as soon as the interrupt pin detects a falling edge in current it will call the broken function
  attachInterrupt(digitalPinToInterrupt(interruptPin), broken, FALLING); 
  //set buttonPin to input
  pinMode(buttonPin, INPUT); //sets button pin to recieve input
  // as soon as the button pin detects a falling edge it calls the changeDisplaySetting function
  attachInterrupt(digitalPinToInterrupt(buttonPin), changeDisplaySetting, FALLING);

  // initializes serial monitor for debug
  Serial.begin(9600);
}

void loop() 
{
  delay(1000); //Time delay on display 
  displayLCD();// displays LCD
 
  //RPM
  if(breakCount >= 30) // as soon as 30 breaks in the tachometer are counted 
 {

  endTime = millis(); // takes current time and stores it as end time.
  
  //there are 60000 milliseconds in one minute and a full rotation is 4 break counts.
  minutes = (endTime - startTime) / 60000; // convert the time to minutes
  rpm = (breakCount / numberOfBlades) / minutes; // calculate rpm, rev/min

  Serial.print("RPM = "); // prints rpm to serial monitor for debugging purposes
  Serial.println(rpm);
  breakCount = 0; //resets the break count so the function will continue to repeat itself
  
 }
   
}

void displayLCD() // After ChangeDisplaySetting is called this function determines what piece of information is displayed
{
   switch(displaySetting) // Depending on the display setting a different piece of information will be displayed
   {
     case 1: //If display setting is one then LCD will display the RPM
     lcd.clear(); // Clears the LCD
     lcd.print("RPM: "); //Tells what information is being displayed
     lcd.print(rpm); // Displays rpm
     lcd.print("rpm"); // Units of rpm
     break; // tells the computer that this statement is over
      
     case 2: //If display setting is one then LCD will display the power
     lcd.clear(); // clears the LCD
     efficiency(); // calls the efficiency function which calculates both power and efficiency
     lcd.print("Power: "); // Tells what is being displayed
     lcd.print(powerOut); // Displays power
     lcd.print("W"); // Units of power
     break; // tells the computer that this statement is over
      
     case 3: //If display setting is one then LCD will display the efficiency
     lcd.clear(); // Clears LCD
     efficiency(); // Calls the efficiency function which calculates both power and efficiency 
     lcd.print("Efficiency: "); // Tells what is being displayed
     lcd.print(eff); // Displays efficiency
     lcd.print("%"); // Efficiency is displayed as a percentage
     break; // tells the computer that this statement is over
      
     default: //serves no real purpose, only to debug, the only way to access this is if an error occured in the code
     lcd.clear(); //Clears LCD
     lcd.print("Unknown Setting!!!!!!!!!!"); // Tells the user something went wrong
   }
 }

void broken () // This function is called everytime the tachometer beam is broken 
{
  if(breakCount == 0) // If this is the first break 
  {
    startTime = millis(); // Start time equals current time
  }

  breakCount++; // Adds one to break count

}

void changeDisplaySetting() // This function handles the change in the display
{
  // If enough time has elapsed since the last display change then the following code is executed.
  if(lastDisplaySwitch +DISPLAY_DELAY < millis()) 
  {
    lastDisplaySwitch = millis(); // Records current time and sets that as the last switch
    // Tells the serial display that the display should be switched, this is mainly used to debug
    Serial.println("Switching display"); 
    displaySetting++; // Increments the display setting so the display will change on the LCD
    
    if(displaySetting>MAX_DISPLAYS) // If the display setting ever increments above the available display options.
    {
      displaySetting = 1; // Resets display setting back to one
    }
    
    displayLCD(); // Calls the display function to actually change the display
  
  }
}
// Calcluates both efficiency and power, all the euqations are found in the LCD part 2 packet or the torque curves
void efficiency() 
{
  nIn = rpm; // Sets nIn to rpm
  nOut = gearRatio * nIn; // Sets nOut to the product of gear ratio and nIn

  torqueOutGCM = (nOut-12800)/-40; // Using the line nOut = -40torqueOutGCM + 12800
  torqueOut = torqueOutGCM * 0.0000980655; //Converts from grams/centimeter to newton*meters
  torqueIn = (torqueOut * nOut) / nIn; // Calculates torqueIn
  powerIn = ((torqueIn * nIn) / 9549) * 1000; //Calculates powerIn
  if (torqueOutGCM <= 48)// If statement determines which relationship to use while calculating efficiency of the motor
  {
    // If torqueOutGCM is less than or equal to 48 use this
    nMotor = (-0.001618 * torqueOutGCM * torqueOutGCM) + (0.363542 * torqueOutGCM) + 49.376500; 
  }
  else
  {
    nMotor = (-0.000434 * torqueOutGCM * torqueOutGCM) - (0.072269 * torqueOutGCM) + 67.566800; // If greater than 48 use this.
  }
  powerInMotor = (-0.000428 * torqueOutGCM * torqueOutGCM) + (0.136943 * torqueOutGCM) + 0.000739; // Calculates powerIn 
  powerOut = (nMotor * powerInMotor)/10; // Calculates powerOut, which is the power that is displayed on the LCD
  
  
  eff = (powerOut / powerIn)*25; // Calculates efficiency which is displayed on the LCD
}



