
/* Define Pins */
const int book_1_Pin = 7;            // Trigger (Relay 1) - for running Book Section 1
const int book_2_Pin = 8;            // Trigger (Relay 2) - for running Book Section 2
const int greenPotion_Pin = 9;       // Trigger (Relay 3) - for running Green Potion Bottle
const int purplePotion_Pin = 10;     // Trigger (Relay 4) - for running Purple Potion Bottle

/* Set Time Variables and Flags */
unsigned long currentTime = millis();                   // Set current time

unsigned long lastTime_book_1;                          // Place to store Time on Book Section 1 animations
unsigned long lastTime_book_1_Off;                      // Place to store Time off Book Section 1 animations
unsigned long lastTime_book_2;                          // Place to store Time on Book Section 2 animations
unsigned long lastTime_book_2_Off;                      // Place to store Time off Book Section 2 animations
unsigned long lastTime_greenPotion;                     // Place to store Time on Green Potion animations
unsigned long lastTime_greenPotion_Off;                 // Place to store Time off Green Potion animations
unsigned long lastTime_purplePotion;                    // Place to store Time on Purple Potions animations
unsigned long lastTime_purplePotion_Off;                // Place to store Time off Purple Potions animations
unsigned long lastTime_book_1_TriggerDelay;             // Place to store Time on Book Section Relay Trigger Delay
unsigned long lastTime_book_2_TriggerDelay;             // Place to store Time on Book Section Relay Trigger Delay

unsigned long duration_book[5] = {5000, 10000, 15000, 20000, 25000};  // Interval Trigger for the Book Case Animations (5 seconds, 10 Sec, 15 sec, 20 sec, 25 sec)
unsigned long duration_bookDelay[3] = {3000, 6000, 9000};             // Interval Delay for the Book Case Animations (3 seconds, 6 Sec, 9 sec)
unsigned long duration_bookTriggerDelay = 500;                        // Amount of time to trigger the Relay - Keep Trigger Relay On (.5 Seconds) - for Both Book Section 1 and 2
unsigned long duration_potion[5] = {3000, 5000, 8000, 10000, 12000};  // Interval Trigger for the Potion Bottle Animations (3 seconds, 5 Sec, 8 sec, 10 sec, 12 sec)
unsigned long duration_potionDelay[3] = {1000, 4000, 6000};           // Interval Delay for the Potion Bottle Animations (1 seconds, 4 Sec, 6 sec)

uint8_t sequenceStep_book_1 = 0;                        // Steps of the animation Sequence for Book Section 1
uint8_t sequenceStep_book_2 = 0;                        // Steps of the animation Sequence for Book Section 2
uint8_t sequenceStep_greenPotion = 0;                   // Steps of the animation Sequence for Green Potion
uint8_t sequenceStep_purplePotion = 0;                  // Steps of the animation Sequence for Purple Potion

uint8_t random_book_1 = 0;                              // Set Initial Random Number
uint8_t random_book_1_Delay = 0;                        // Set Initial Random Number
uint8_t random_book_2 = 0;                              // Set Initial Random Number
uint8_t random_book_2_Delay = 0;                        // Set Initial Random Number
uint8_t random_greenPotion = 0;                         // Set Initial Random Number
uint8_t random_greenPotion_Delay = 0;                   // Set Initial Random Number
uint8_t random_purplePotion = 0;                        // Set Initial Random Number
uint8_t random_purplePotion_Delay = 0;                  // Set Initial Random Number


/* Function ProtoTypes */
void book_1();
void book_2();
void greenPotion();
void purplePotion();

void setup() {

  randomSeed(3);                                        // Start the random number generator with number (3)

/* Set Pins */
  pinMode(book_1_Pin, OUTPUT);                          // Set Relay as output
  pinMode(book_2_Pin, OUTPUT);                          // Set Relay as output  
  pinMode(greenPotion_Pin, OUTPUT);                     // Set Relay as output  
  pinMode(purplePotion_Pin, OUTPUT);                    // Set Relay as output

  digitalWrite(greenPotion_Pin, LOW);                   // Start with Potions off
  digitalWrite(purplePotion_Pin, LOW);  

/* Turn off Books at start */
  delay(1000);                                          // Delay 1 second
  digitalWrite(book_1_Pin, HIGH);                       // Simulate button press to turn off... Push button/Turn on Relay
  digitalWrite(book_2_Pin, HIGH);
  delay(duration_bookTriggerDelay);                     // Wait for 1/2 - simulated button press
  digitalWrite(book_1_Pin, LOW);                        // Turn off Relays - Should start Bookcase in off position
  digitalWrite(book_2_Pin, LOW);
  delay(1000);                                          // Delay 1 second
}

void loop() {
  currentTime = millis();                                             // Update current Time
  book_1();
  book_2();
  greenPotion();
  purplePotion();
}

void book_1() {
  if (sequenceStep_book_1 == 0) {                                     // Check Sequence Step
    random_book_1 = random(0,5);                                      // Set Random Numbers
    random_book_1_Delay = random(0,3);                        
    sequenceStep_book_1 = 1;                                          // Go to Next Step
  }
  if (sequenceStep_book_1 == 1) {                                     // Check Sequence Step
    digitalWrite(book_1_Pin, HIGH);                                   // Turn on Relay for Book Station 1
    lastTime_book_1 = currentTime;                                    // Set last Time book run
    lastTime_book_1_TriggerDelay = currentTime;                       // Set Relay Trigger Delay Timer
    sequenceStep_book_1 = 2;                                          // Go to Next Step
  }
  if (sequenceStep_book_1 == 2) {                                     // Check Sequence Step
    if ((currentTime - lastTime_book_1_TriggerDelay) > duration_bookTriggerDelay) {
      digitalWrite(book_1_Pin, LOW);                                  // Turn off Relay after relay timer has passed
    }
    if ((currentTime - lastTime_book_1) > duration_book[random_book_1]) {            // Check if enough time has passed
      digitalWrite(book_1_Pin, HIGH);                                 // Turn on Relay for Book Station 1
      lastTime_book_1_Off = currentTime;                              // Reset last Time book run variable for off cycle
      lastTime_book_1_TriggerDelay = currentTime;                     // Set Relay Trigger Delay Timer
      sequenceStep_book_1 = 3;                                        // Go to Next Step
    }
  }  
  if (sequenceStep_book_1 == 3) {                                     // Check Sequence Step
    if ((currentTime - lastTime_book_1_TriggerDelay) > duration_bookTriggerDelay) {
      digitalWrite(book_1_Pin, LOW);                                  // Turn off Relay after relay timer has passed
    }
    if ((currentTime - lastTime_book_1_Off) > duration_bookDelay[random_book_1_Delay]) {      // Check if enough time has passed
      sequenceStep_book_1 = 0;                                        // Go to Beginning Step
    }
  }  
}

void book_2() {
  if (sequenceStep_book_2 == 0) {                                     // Check Sequence Step
    random_book_2 = random(0,5);                                      // Set Random Numbers
    random_book_2_Delay = random(0,3);                        
    sequenceStep_book_2 = 1;                                          // Go to Next Step
  }
  if (sequenceStep_book_2 == 1) {                                     // Check Sequence Step
    digitalWrite(book_2_Pin, HIGH);                                   // Turn on Relay for Book Station 2
    lastTime_book_2 = currentTime;                                    // Set last Time book run
    lastTime_book_2_TriggerDelay = currentTime;                       // Set Relay Trigger Delay Timer
    sequenceStep_book_2 = 2;                                          // Go to Next Step
  }
  if (sequenceStep_book_2 == 2) {                                     // Check Sequence Step
    if ((currentTime - lastTime_book_2_TriggerDelay) > duration_bookTriggerDelay) {
      digitalWrite(book_2_Pin, LOW);                                  // Turn off Relay after relay timer has passed
    }
    if ((currentTime - lastTime_book_2) > duration_book[random_book_2]) {            // Check if enough time has passed
      digitalWrite(book_2_Pin, HIGH);                                 // Turn on Relay for Book Station 2
      lastTime_book_2_Off = currentTime;                              // Reset last Time book run variable for off cycle
      lastTime_book_2_TriggerDelay = currentTime;                     // Set Relay Trigger Delay Timer
      sequenceStep_book_2 = 3;                                        // Go to Next Step
    }
  }  
  if (sequenceStep_book_2 == 3) {                                     // Check Sequence Step
    if ((currentTime - lastTime_book_2_TriggerDelay) > duration_bookTriggerDelay) {
      digitalWrite(book_2_Pin, LOW);                                  // Turn off Relay after relay timer has passed
    }
    if ((currentTime - lastTime_book_2_Off) > duration_bookDelay[random_book_2_Delay]) {      // Check if enough time has passed
      sequenceStep_book_2 = 0;                                        // Go to Beginning Step
    }
  }   
}

void greenPotion() {
  if (sequenceStep_greenPotion == 0) {                                       // Check Sequence Step
    random_greenPotion = random(0,5);                                        // Set Random Numbers
    random_greenPotion_Delay = random(0,3);                        
    sequenceStep_greenPotion = 1;                                            // Go to Next Step
  }
  if (sequenceStep_greenPotion == 1) {                                       // Check Sequence Step
    digitalWrite(greenPotion_Pin, HIGH);                                     // Turn on Relay for Green Potion
    lastTime_greenPotion = currentTime;                                      // Set last Time book run
    sequenceStep_greenPotion = 2;                                            // Go to Next Step
  }
  if (sequenceStep_greenPotion == 2) {                                       // Check Sequence Step
    if ((currentTime - lastTime_greenPotion) > duration_potion[random_greenPotion]) {         // Check if enough time has passed
      digitalWrite(greenPotion_Pin, LOW);                                    // Turn off Relay
      lastTime_greenPotion_Off = currentTime;                                // Reset last Time book run variable for off cycle
      sequenceStep_greenPotion = 3;                                          // Go to Next Step
    }
  }  
  if (sequenceStep_greenPotion == 3) {                                       // Check Sequence Step
    if ((currentTime - lastTime_greenPotion_Off) > duration_potionDelay[random_greenPotion_Delay]) {   // Check if enough time has passed
      sequenceStep_greenPotion = 0;                                          // Go to Beginning Step
    }
  }
}

void purplePotion() {
  if (sequenceStep_purplePotion == 0) {                                      // Check Sequence Step
    random_purplePotion = random(0,5);                                       // Set Random Numbers
    random_purplePotion_Delay = random(0,3);                        
    sequenceStep_purplePotion = 1;                                           // Go to Next Step
  }
  if (sequenceStep_purplePotion == 1) {                                      // Check Sequence Step
    digitalWrite(purplePotion_Pin, HIGH);                                    // Turn on Relay for Purple Potion
    lastTime_purplePotion = currentTime;                                     // Set last Time book run
    sequenceStep_purplePotion = 2;                                           // Go to Next Step
  }
  if (sequenceStep_purplePotion == 2) {                                      // Check Sequence Step
    if ((currentTime - lastTime_purplePotion) > duration_potion[random_purplePotion]) {       // Check if enough time has passed
      digitalWrite(purplePotion_Pin, LOW);                                   // Turn off Relay
      lastTime_purplePotion_Off = currentTime;                               // Reset last Time book run variable for off cycle
      sequenceStep_purplePotion = 3;                                         // Go to Next Step
    }
  }  
  if (sequenceStep_purplePotion == 3) {                                      // Check Sequence Step
    if ((currentTime - lastTime_purplePotion_Off) > duration_potionDelay[random_purplePotion_Delay]) { // Check if enough time has passed
      sequenceStep_purplePotion = 0;                                         // Go to Beginning Step
    }
  }
}