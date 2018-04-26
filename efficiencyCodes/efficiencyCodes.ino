void setup() {
 

}

void loop() 
{
  //RPM
  if (breakCount >= 30)
  { 
    endTime = millis(); // Sets endTime equal to the current milliseconds
    double x = (double)breakCount/numberOfBlades;
    double y = (double)(endTime-startTime)/60000; 
    rpm = x/y; // Equates and sets the rpm as an integer
    Serial.print("The rpm is "); // Prints "The rpm is " to the serial interface
    Serial.println(rpm); // Prints the rpm to the serial interface then a new line character
    breakCount = 0; // Resets the breakCount to 0
  }

  


  // Other Calculations Code
  n_in = rpm; //tachometer
  nt_in = 64; //# of gear teeth DC motor input shaft
  nt_out = 8; //# of gear teeth windmill output shaft
  gearRatio = nt_in / nt_out;
  n_out = gearRatio * n_in;
  
  t_out_gcm = (n_out-12800)/-40; // y=-40x+12800 -> (y-12800)/-40 = x
  t_out_nm = t_out_gcm * 0.0000980655;
  t_in = t_out_nm * n_out / n_in; // tin = tout * nout / nin, in Nm
  p_in = t_in * n_in / 9549 * 1000; //in W
  if (t_out_gcm <= 48){
    n_motor = -0.001618 * t_out_gcm * t_out_gcm + 0.363542 * t_out_gcm + 49.376500;
  }else{
    n_motor = -0.000434 * t_out_gcm * t_out_gcm - 0.072269 * t_out_gcm + 67.566800;
  }
  p_inmotor = -0.000428 * t_out_gcm * t_out_gcm + 0.136943 * t_out_gcm + 0.000739;
  p_out = n_motor * p_inmotor;
  
  n = p_out / p_in;
//


//GLOBAL POWER OUT VARIABLES
double Vr, I, pOut1;
double Vtotal = 9.28;

//*THE POWER OUT STUFFS IS LIKE THE DC MOTOR CIRCUIT LESSON*

//Efficiency Helper
double findEfficiency(){
  nIn = rpm;
  nOut = nIn * 8;
 
  //tOut expression found using points on data trend graphs given
  tOut = (12800 - nOut) / 407886.485;

  tIn = (tOut * nOut) / nIn;

  //From video; for power in expression; IN WATTS
  pIn = ((tIn * nIn) / 9549) * 1000;

  pOut = findPowerOut();

  eff = ((float)powerOut / (float)powerIn) * 100; //percent

  return eff;
}

//Efficiency find powerOut Helper
int findPowerOut(){
  int voltageDrop = analogRead(A5);
  if(voltageDrop > 0){
  Vr = (double)voltageDrop;
  Vr = Vr * Vtotal / 1024;
  I = Vr / 1;
  pOut1 = (Vtotal - Vr) * I;
  }

 
}
