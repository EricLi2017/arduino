/* Sweep
  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Sweep
*/
#include <Servo.h>
//declare servo pins
const int SERVO_PIN = 9;//a pwm pin for servo

//delcare HC-SR04 ultrasonic sensor pins
const int TRIG_PIN = 2;
const int ECHO_PIN = 3;

//delcare the servo positions
const int POS_FRONT = 90; //front
const int POS_LEFT = 160; //left
const int POS_RIGHT = 10; //right

//delcare the servo wait times in millseconds
const unsigned long TIME_SERVO_WAIT = 500;

//delcare the dangerous distance in cm
const int STOP_DISTANCE = 15; //cm

//delcare servo object
// twelve servo objects can be created on most boards
// create servo object to control a servo
Servo myServo;

//declare the current position of the servo
int pos = 0;

//declare distance of obstacles
float cmFront;//the distance to the front obstacle in CM
float cmLeft;//the distance to the left obstacle in CM
float cmRight;//the distance to the right obstacle in CM

//delcare the now time
unsigned long now;

void setup() {
  Serial.begin(9600);

  // attaches the servo on SERVO_PIN to the servo object
  myServo.attach(SERVO_PIN);

  //set pin mode for HC-SR04 ultrasonic sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  //update the now time
  now = millis();

  //update front obstacle distance
  cmFront = getDistance();
  Serial.print(" cmFront ");
  Serial.print(cmFront );
  Serial.println(" CM");

  if (cmFront < STOP_DISTANCE) {
    Serial.print(now);
    Serial.print("  ");
    Serial.print(millis());
    Serial.print(" stop the car, obstacle in front ");
    Serial.print(cmFront);
    Serial.println(" CM");//TODO for test

    Serial.print("update both sides distance start at ");
    Serial.println( millis());
    updateBothSidesDistance();
    Serial.print(" cmRight ");
    Serial.print(cmRight);
    Serial.print(" CM");
    Serial.print(" cmLeft ");
    Serial.print(cmLeft );
    Serial.println(" CM");
    Serial.print("update both sides distance end at ");
    Serial.println(millis());
  }

  // servo drive HC-SR04 ultrasonic sensor turn around and get all distance of three directions
  //  updateThreeDistance();

  //print all distance of three directions
  printLog(POS_RIGHT, cmRight);
  printLog(POS_FRONT, cmFront);
  printLog(POS_LEFT, cmLeft);

  //car run
  carRun();
}

