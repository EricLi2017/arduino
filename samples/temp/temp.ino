// English for which LED to Strobe
#define RED 0x0
#define BLUE 0x1

// Variable to track which LED is on
byte whichLED = RED;

// Where are the LEDs connected?
const int LED_RED_PIN = 10;
const int LED_BLUE_PIN = 11;

// State variables for the LEDs
byte redState = LOW;
byte blueState = LOW;

// Some delay values to change flashing behavior
//unsigned long SWITCH_DELAY = 250;
const unsigned long SWITCH_DELAY = 600;
const unsigned long STROBE_DELAY = 100;

// Seed the initial wait for the strobe effect
unsigned long strobeWait = STROBE_DELAY;

// Variable to see when we should swtich LEDs
unsigned long waitUntilSwitch = SWITCH_DELAY;  // seed initial wait

void setup() {
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_RED_PIN, HIGH);     // each iteration of loop() will set the IO pins,
  digitalWrite(LED_BLUE_PIN, LOW);    // even if they don't change, that's okay


}
