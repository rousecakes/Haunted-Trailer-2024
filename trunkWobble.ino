#include <AccelStepper.h>


/* AccelStepper Setup */
AccelStepper stepperS(1, 12, 13);   // 1 = Driver Interface (TB6600)*** Changed to DM542T 05/2023 *** Changed to DM860T(V3.0) 07/2023
                                    // Arduino Pin 12 Connected to STEP Pin of Driver
                                    // Arduino Pin 13 Connected to DIR Pin of Driver
                                    // 800 Steps per Revolution - 1.8 Deg Per Step

/* DEFINE Consstraints/Pins */


/* Stepper Travel Variables and Initializers */
const int motorSpeed = 450;                                    // Keep between 150-1000, Lower equal slower
unsigned long stepperVar = 1;                                  // A Place to hold Step location

uint8_t randomNumber_delay;                                    // Variable for random delay
uint16_t buffer_delay[3] = { 500, 1500, 2500 };                // Delays to stay at position (1/2 Seconds, 1-1/2 Seconds, 2-1/2 Seconds)

unsigned long currentTime = millis();                          // Set Time Variable
unsigned long lastTime_knockDelay;                             // Place to store Time on Knock Wheel Delay
unsigned long duration_knockDelay = 5000;                      // Delay Interval on Knock Wheel - 5 seconds
unsigned long lastTime_handEvent;                              // Place to store Time on the Hand Event
unsigned long duration_handEvent = 90000;                      // Interval Trigger for Hand Event - 1.5 Mins



/* Function ProtoTypes */


void setup() {
  Serial.begin(9600);                                // Start Serial Monitor with speed of 9600 Bauds
  delay(5);                                          // Wait for Driver to startup
  stepperS.setCurrentPosition(0);                    // Set Current Position to Zero  
  stepperS.setMaxSpeed(motorSpeed + 1);              // Set Max Speed of Stepper (Slower to get accuracy)
  stepperS.setAcceleration(motorSpeed);              // Set Acceleration of the Stepper
  stepperS.setSpeed(motorSpeed);                     // Set Speed of Stepper
  randomSeed(3);                                     // Start Random Seed for use of Random Function Later
}

void loop() {
  currentTime = millis();                                            // Update current Time
  //stepperS.moveTo(stepperVar);                                         // Set step to move to 1 step forward
  stepperS.runSpeed();                                               // Run Stepper 1 Step
  //stepperVar ++;
  if ((currentTime - lastTime_knockDelay) > duration_knockDelay){    // Check to see if enough time has passed to pick a random wheel delay
    randomNumber_delay = random(0,3);                                // Pick Random Delay
    delay(buffer_delay[randomNumber_delay]);                         // Delay before next movement or cycle
    lastTime_knockDelay = currentTime;                               // Reset Timer as event is complete
  } 
} 
  
