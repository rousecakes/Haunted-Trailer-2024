
/* Define Pins */
const int cycleSwitch = A0;                 // Switch for Cycle animation Flag
const int piston = A1;                      // Air Cylinder (Relay 1) - For sending Book forward
const int animationTrigger = A2;            // Trigger (Relay 2) - for starting book animations
const int eventButton = A3;                 // Button to Initiate book event


/* Set Time Variables and Flags */
unsigned long currentTime = millis();                                                                         // Set current time

unsigned long lastTime_sendBook;                                                                              // Place to store Time on the Book Event
unsigned long duration_sendBook = 90000;                                                                      // Interval Trigger for the Book Event - 1.5 Mins
unsigned long duration_animationStartDelay = 0;                                                               // Amount of seconds to delay the start of animation (0 Seconds - Start Immediatly) - Animation itself is 9-10 Seconds in total
unsigned long duration_animationTriggerDelay = 500;                                                           // Amount of time to trigger the animation - Keep Trigger Relay On (Half a Second)
unsigned long duration_pistonDelay = (7500UL-duration_animationStartDelay-duration_animationTriggerDelay);    // Amount of time to leave piston on (7.5 Seconds)
unsigned long duration_animationComplete = (10000UL-duration_pistonDelay-duration_animationTriggerDelay);     // Remainder of the animation cycle ([10000]-"duration_animationComplete"[7000]-duration_animationTriggerDelay[500] = 2500 or 2.5 Seconds)

/* Function ProtoTypes */
void sendBook();

void setup() {

/* Set Pins */
  pinMode(cycleSwitch, INPUT_PULLUP);       // Set cycle switch as input; pulled high internally; Ground to activate switch
  pinMode(eventButton, INPUT_PULLUP);       // Set event button as input; pulled high internally; Ground to activate switch
  pinMode(piston, OUTPUT);                  // Set Piston position as Output
  pinMode(animationTrigger, OUTPUT);        // Set trigger as output
}

void loop() {
  currentTime = millis();                                             // Update current Time
  if(digitalRead(cycleSwitch) == HIGH) {                              // Check to see if Cycle switch is on
    if ((currentTime - lastTime_sendBook) > duration_sendBook) {      // Check to see if enough time has passed to trigger book event
      sendBook();                                                     // Run Book Event Function
      lastTime_sendBook = currentTime;                                // Reset Timer for book event as it has just been completed
    }  
  }
  if (digitalRead(eventButton) == LOW) {                              // Check to see if Event button Pressed
    Serial.println("Button Pressed");                                 // Send Debug text to serial monitor
    sendBook();                                                       // Run book event
  }
}

void sendBook() {
  digitalWrite(piston, HIGH);             // Turn on piston/air cylinder (extend air cylinder)
  delay(duration_animationStartDelay);    // delay the animation start delay
  digitalWrite(animationTrigger, HIGH);   // Turn on book animation Relay
  delay(duration_animationTriggerDelay);  // Delay to make sure animation is triggered
  digitalWrite(animationTrigger, LOW);    // Turn off animation Relay - Book animation has been triggered and will continue to play on book animation board
  delay(duration_pistonDelay);            // Leave piston extended for a period of time - Piston travel time set by air throttles on cylinder ports
  digitalWrite(piston, LOW);              // Turn off Piston relay (retract air cylinder)
  delay(duration_animationComplete);      // Delay the remainder of the animation before re entering main loop
}
