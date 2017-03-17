/*
  ManualVelocityMode
  Runs a Teknic Clearpath motor in manual Velocity mode, back and forth
 
 
 This example code is in the public domain.
 */



//Import Required libraries
#include <ManVelClearpath.h>

// initialize a ManVelClearpath Motor
ManVelClearpath X;

//initialize the controller and pass the reference to the motor we are controlling
void setup()
{  
  //DEBUG declare pin 2 as output.  Abe, this shows when the arduino is in the ISR
  pinMode(2,OUTPUT);
  
  //Begin Serial Communication  NOTE: WHEN GOING FAST, communication may lag
  Serial.begin(9600);
  
//X.attach(10,11);        //Quad A is pin 10, Quad B is pin 11
//X.attach(10,11,5);      //Quad A is pin 10, Quad B is pin 11, Enable is pin 5
  X.attach(10,11,5,3);    //Quad A is pin 10, Quad B is pin 11, Enable is pin 5, HLFB is pin 4

// Enable motor 
X.enable();

// Wait for motor to become enabled (delayed because of slight filtering)
delay(15);
 
}

void loop()
{  
// Ramp up speed CW to 1000*resolution in MSP  NOTE: This command can take several milliseconds to execute
   X.speed(1000);
   Serial.print("New Commanded Speed:  ");
   Serial.println(X.getSpeed());
   delay(100);
   
// Wait until HLFB becomes asserted (asserted may mean true or false depending on wiring of HLFB)
  while(X.readHLFB())
   { 
   }
   Serial.println("Acheived Speed");
   delay(1000);

// Ramp up speed CCW to 1000*resolution in MSP  NOTE: This command can take several milliseconds to execute   
   X.speed(-1000);
   Serial.print("New Commanded Speed:  ");
   Serial.println(X.getSpeed());
   delay(100);
 // Wait until HLFB becomes asserted (asserted may mean true or false depending on wiring of HLFB)
   while(X.readHLFB())
   { 
   }
   Serial.println("Acheived Speed");
   delay(1000);
}
