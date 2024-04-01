/* Define Pins */
const int cycleSwitch = A0;                 // Switch for Cycle animation Flag
const int eventButton = A1;                 // Button to Initiate Dragon Breath (Fire) event
const int fireSwitch = 7;                   // Trigger (Relay 1) - for starting Dragon Breath (Fire)

/* Set Time Variables and Flags */
unsigned long currentTime = millis();                             // Set current time
const unsigned long Interval_fire[3] = { 9000, 20000, 30000 };    // Interval Array of time to set random numbers for dragon breath (fire) ** Lowest Number Must be Larger then Largest number in "Duration_spit" Array 
const unsigned long Duration_fire[3] = { 500, 1000, 1750 };       // Duration Array for Fire Time (Seconds)
bool fireState = false;                                           // Variable to turn off and on (Fire) Fog Machine
bool eventState = false;                                          // Variable to track event button states

/* Function ProtoTypes */
void dragonFire();

void setup() {
  Serial.begin(9600);           // Start Serial Monitor with speed of 9600 Bauds
  randomSeed(3);                // Start Random Seed for use of Random Function Later
  
/* Set Pins */
  pinMode(cycleSwitch, INPUT_PULLUP);       // Set cycle switch as input; pulled high internally; Ground to activate switch
  pinMode(eventButton, INPUT_PULLUP);       // Set event button as input; pulled high internally; Ground to activate switch
  pinMode(fireSwitch, OUTPUT);              // Set trigger as output
}

void loop() {
  currentTime = millis();                   // Update current Time
  if (digitalRead(cycleSwitch) == HIGH) {   // Check to see if Cycle switch is on
    dragonFire();                           // Run Dragon Breath (Fire) Event Function
    if (digitalRead(eventButton) == LOW) {  // If Button Pressed...
      digitalWrite(fireSwitch, HIGH);       // Turn On Fire Fog Machine
      eventState = true;                    // Increment Event State
    }
    if ((digitalRead(eventButton) == HIGH) && (eventState == true)) {   // Event Button Just Released
      if (fireState == false) {
        digitalWrite(fireSwitch, LOW);      // Turn Off Fire Fog Machine
      }
      eventState = false;                   // Turn Off Event button Flag
    }
  } else {
    digitalWrite(fireSwitch, LOW);          // If Cycle switch low - Turn Off Fire Fog Machine
  }
}

void dragonFire () {
  static unsigned long lastTime_fire;                             // Variable to hold Last time action happened 
  static unsigned long lastTime_fireDuration;                     // Variable to hold Last time action happened 
  static unsigned long randomNumber_fireInterval;                 // Variable to hold random number for Dragon Breath (Fire) Interval
  static unsigned long randomNumber_fireDuration;                 // Variable to hold random number for Dragon Breath (Fire) Duration  

  if ((currentTime - lastTime_fire) >= Interval_fire[randomNumber_fireInterval]) {           // Check to See if the Duration of Time has Passed in order to Breath Fire Again
    if (fireState == false) {                                                                // If Fire Switch off (not Breathing Fire)... 
      digitalWrite(fireSwitch, HIGH);                                                        // ...Turn Fire Switch on (start Breathing Fire)
      fireState = true;                                                                      // Change Spit State to True because we are now breathing fire!
      randomNumber_fireDuration = random(3);                                                 // Pick New Random Duration Dragon should Breathe Fire for
      lastTime_fireDuration = currentTime;                                                   // Reset Dragon Fire Duration Timer to start tracking Fire Duration
    }
  }
  if ((currentTime - lastTime_fireDuration) >= Duration_fire[randomNumber_fireDuration]) {   // Check to See if the Duration of Time has Passed for Length of Fire
    if (fireState == true) {                                                                 // If Fire Flag is on (still Breathing Fire)...
      digitalWrite(fireSwitch, LOW);                                                         // ...Turn off Fire Fog Machine
      fireState = false;                                                                     // Turn off Fire Flag
      randomNumber_fireInterval = random(3);                                                 // Pick New Random Interval to Wait for Next Fire Cycle
      lastTime_fire = currentTime;                                                           // Reset Fire Interval Timer to start tracking When to Fire Again
    }
  }
}
