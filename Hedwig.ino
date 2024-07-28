
/* Define Pins */
const int animationTrigger = 15;            // Trigger (Relay 1) - for running hedwig animations



/* Set Time Variables and Flags */
unsigned long currentTime = millis();                   // Set current time

unsigned long lastTime_hedwig;                          // Place to store Time on Hedwig animations
unsigned long duration_hedwig = 60000;                  // Interval Trigger for the Hedwig Animations (1 Min)
unsigned long duration_animationTriggerDelay = 5000;    // Amount of time to trigger the animation - Keep Trigger Relay On (5 Second)
unsigned long lastTime_animationTriggerDelay;           // Place to store Time on Hedwig animation Trigger Delay
uint8_t sequenceStep = 0;                               // Steps fof the animation Sequence

/* Function ProtoTypes */

void setup() {

/* Set Pins */
  pinMode(animationTrigger, OUTPUT);        // Set trigger as output

  digitalWrite(animationTrigger, HIGH);
  lastTime_hedwig = currentTime;
}

void loop() {
  currentTime = millis();                                             // Update current Time
  if ((currentTime - lastTime_hedwig) > duration_hedwig) {            // If time Has Passed
    if (sequenceStep == 0) {                                          // Check Sequence Step
      digitalWrite(animationTrigger, LOW);                            // Turn off Relay for animations
      lastTime_animationTriggerDelay = currentTime;                   // Reset Delay Variable
      sequenceStep = 1;                                               // Move to next step
    }
    if (sequenceStep == 1) {                                                                        // next Sequence Step
      if ((currentTime - lastTime_animationTriggerDelay) > duration_animationTriggerDelay) {        // Check to See if Time Elapsed for Trigger
        digitalWrite(animationTrigger, HIGH);                                                       // Turn on Relay for animations
        lastTime_hedwig = currentTime;                                                              // Reset Hedwig Timer
        sequenceStep = 0;                                                                          // Reset Sequence Step
      }
    }  
  }
}