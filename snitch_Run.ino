#include <AccelStepper.h>

/* AccelStepper Setup */
AccelStepper stepperS(1, 12, 13);     // 1 = Driver Interface DM542T - Set steps to 800 Per Rotation
                                      // Arduino Pin 12 Connected to STEP Pin of Driver
                                      // Arduino Pin 13 Connected to DIR Pin of Driver

/* DEFINE Consstraints/Pins */
const int pot = A0;                   // Pin A0 Connected to center pin [2] on Potentiometer (Pot Pin 1 connected to +5V, Pot Pin 3 connected to Gnd)

/* Stepper Travel Variables and Initializers */
const int maxMotorSpeed = 2000;       // Keep between 50-3000, Lower equal slower
const int startMotorSpeed = 0;        // Lower equal slower
const int acceleration = 400;         // Acceleration Keep between 50-maxMotorSpeed
 
int previousRead = 0;                                // Set Variable for previous reading

void setup() {
  Serial.begin(9600);                                // Start Serial Monitor with speed of 9600 Bauds
  delay(5);                                          // Wait for Driver to startup
  stepperS.setCurrentPosition(0);                    // Set Current Position to Zero  
  stepperS.setMaxSpeed(maxMotorSpeed);               // Set Max Speed of Stepper (Slower to get accuracy)
  stepperS.setAcceleration(acceleration);            // Set Acceleration of the Stepper
  stepperS.setSpeed(startMotorSpeed);                // Set Speed of Stepper to start

  /* Set Pins */
  pinMode(pot, INPUT);                               // Set Potentiometer as an Input

  // previousRead = analogRead(pot);                    // Set Variable to start motor at 0 speed **** Turn on if you want Snitch not to move until pot turned when booted up
}

void loop() {

  int sensorReading = analogRead(pot);                                                       // Read the senor value (on poteniometer)
  if (sensorReading < 5) {                                                                   // Check to see is the Value is at the end/Off Position - This takes care of Anomoly Steps from analog read)
    stepperS.setSpeed(0);                                                                    // Set Speed to Zero
  } else if ((sensorReading > previousRead+6) || (sensorReading < previousRead-6)) {         // Check that a move of the pot is at least > or < than 6
      int long sensorReadingMap = map(sensorReading, 0, 1023, 0, maxMotorSpeed);             // Map Pot Reading to Speed Range ((2000 steps per second / 800 Per Rev)*60 Seconds = 150 RPM)
      stepperS.setSpeed(sensorReadingMap);                                                   // Set the Speed to the Mapped Value
      previousRead = sensorReading;                                                          // Reset/Update the previous read variable
  }
  stepperS.runSpeed();                               // Run Stepper 1 Step
}
