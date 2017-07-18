// English for which LED to Strobe
#define RED 0x0
#define BLUE 0x1

// Variable to track which LED is on
byte whichLED = RED;



// State variables for the LEDs
byte redState = LOW;
byte blueState = LOW;

// Some delay values to change flashing behavior
//unsigned long SWITCH_DELAY = 250;
const unsigned long SWITCH_DELAY = 300;
const unsigned long STROBE_DELAY = 50;

// Seed the initial wait for the strobe effect
unsigned long strobeWait = STROBE_DELAY;

// Variable to see when we should swtich LEDs
unsigned long waitUntilSwitch = SWITCH_DELAY;  // seed initial wait

//led storbe
void ledStorbe() {
  digitalWrite(LED_RED_PIN, redState);     // each iteration of loop() will set the IO pins,
  digitalWrite(LED_BLUE_PIN, blueState);    // even if they don't change, that's okay

  // Toggle back and forth between the two LEDs
  if ((long)(millis() - waitUntilSwitch) >= 0) {
    // time is up!
    redState = LOW;
    blueState = LOW;
    whichLED = !whichLED;  // toggle LED to strobe
    waitUntilSwitch += SWITCH_DELAY;
  }

  // Create the stobing effect
  if ((long)(millis() - strobeWait) >= 0) {
    if (whichLED == RED)
      redState = !redState;
    if (whichLED == BLUE)
      blueState = !blueState;
    strobeWait += STROBE_DELAY;
  }
}

//void ledUpdate() {
//  digitalWrite(LED_RED_PIN, redState);     // each iteration of loop() will set the IO pins,
//  digitalWrite(LED_BLUE_PIN, blueState);    // even if they don't change, that's okay
//}
