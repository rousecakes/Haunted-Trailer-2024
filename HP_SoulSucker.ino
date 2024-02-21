
/* Define Pins */
const int cycleSwitch = A0;                 // Switch for Cycle animation Flag
const int eventButton = A1;                 // Button to Initiate book event
const int animationTrigger = A2;            // Trigger (Relay 2) - for starting book animations



/* Set Time Variables and Flags */
unsigned long currentTime = millis();                   // Set current time

unsigned long lastTime_suckSoul;                        // Place to store Time on the Book Event
unsigned long duration_suckSoul = 90000;                // Interval Trigger for the Book Event (1.5 Mins)
unsigned long duration_animationTriggerDelay = 500;     // Amount of time to trigger the animation - Keep Trigger Relay On (Half a Second)
unsigned long duration_animationComplete = 10000;       // Remainder of the animation cycle (10 Seconds)

/* Function ProtoTypes */
void suckSoul();

void setup() {

/* Set Pins */
  pinMode(cycleSwitch, INPUT_PULLUP);       // Set cycle switch as input; pulled high internally; Ground to activate switch
  pinMode(eventButton, INPUT_PULLUP);       // Set event button as input; pulled high internally; Ground to activate switch
  pinMode(animationTrigger, OUTPUT);        // Set trigger as output
}

void loop() {
  currentTime = millis();                                             // Update current Time
  if(digitalRead(cycleSwitch) == HIGH) {                              // Check to see if Cycle switch is on
    if ((currentTime - lastTime_suckSoul) > duration_suckSoul) {      // Check to see if enough time has passed to trigger book event
      suckSoul();                                                     // Run Soul Sucker Event Function
      lastTime_suckSoul = currentTime;                                // Reset Timer for book event as it has just been completed
    } else if (digitalRead(eventButton) == LOW) {                     // Check to see if Event button Pressed
    Serial.println("Button Pressed");                                 // Send Debug text to serial monitor
    suckSoul();                                                       // Run Soul Sucker event
    }  
  }
}

void suckSoul() {
  digitalWrite(animationTrigger, HIGH);   // Turn on book animation Relay
  delay(duration_animationTriggerDelay);  // Delay to make sure animation is triggered
  digitalWrite(animationTrigger, LOW);    // Turn off animation Relay - Book animation has been triggered and will continue to play on book animation board
  delay(duration_animationComplete);      // Delay the remainder of the animation before re entering main loop
}
