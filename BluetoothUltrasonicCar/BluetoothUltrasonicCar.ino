/**
  Ultrasonic obstacle avoidance automatic driving car or bluetooth control car


  Motor Driver L298N

  Servo SG90
  3 lines: VCC(red),GND(grown),IN(orange)
  VCC: 4.8-7.2V
  4.2-6V

  Ultrasonic sensor HC-SR04
  Pins: VCC,Trig,Echo,GND
  VCC: 5V
  Current: 2mA
  Trig:  HIGH >= 10us, circle >= 60ms

  LCD 1602 & IIC
  Pins: VCC,GND,SDA,SCL
  VCC: 5V
  IIC/I2C: SDA(A4),SCL(A5)


  Bluetooth HC-05
  Used pin:VCC,GND,TXD,RXD
  VCC: 3.6V-6V
  TXD:  UNO RXD
  RXD:  UNO TXD

  Eric
  2016-12-31  draft
  2017-01-02  v1.0
  2017-01-04  v1.1
  2017-01-05  v2.0 draft
  2017-01-06  v2.0 draft update
  2017-01-07  v2.0
  (suit for client Rluetooth RC Controll,
  client setting: continus stream every 50ms, and contiuns send stop cmd while no touch)
  2017-01-11  v2.1 support turn on/off LCD backlight
  2017-01-23  v2.2 add red blue led storbe function (turn on/off LCD CMD to control this function)
*/
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

//
//delcare the arduino uno r3 pins
//
//declare servo pins
const int SERVO_PIN = 9;//a PWM pin for servo
//delcare HC-SR04 ultrasonic sensor pins
const int TRIG_PIN = 2;
const int ECHO_PIN = 3;
//declare motor pins
//from left to right
const int MOTORA_1_PIN = 4;   //LEFT 1: IN1
const int MOTORA_2_PIN = 5;   //LEFT 2: IN2
const int MOTORB_1_PIN = 6;  //RIGHT 1:  IN3
const int MOTORB_2_PIN = 7;  //RIGHT 2:  IN4
//delcare buzzer pin
const int BUZZER_PIN = 8;
//declare bluetooth pins
//only use VCC,GND,TXD,RXD pins
//delcare blue+red led pins
const int LED_RED_PIN = 10;
const int LED_BLUE_PIN = 11;

//
//declare driving elements
//
const int DRIVE_MODE_FREE = 0;  //free driving mode: auto driving
const int DRIVE_MODE_OBSTACLE = 1; //obstacle avoidance mode
const int DRIVE_MODE_CMD = 2; //command mode: under bluetooth command mode
const int DRIVE_DIRECTION_FORWARD = 1;  //go forward
const int DRIVE_DIRECTION_BACKWARD = 2; //go backward
const int DRIVE_DIRECTION_LEFT = 3;     //turn left
const int DRIVE_DIRECTION_RIGHT = 4;    //turn right
const int DRIVE_DIRECTION_STOP = 5;     //stay in place /stop
const unsigned long DRIVE_DURATION_OBSTACLE_LEFT = 600; //milliseconds,the turn left driving time under obstacle avoidance mode
const unsigned long DRIVE_DURATION_OBSTACLE_RIGHT = 600; //milliseconds,the turn right driving time under obstacle avoidance mode
const unsigned long DRIVE_DURATION_OBSTACLE_FORWARD = 600; //milliseconds,the go forward driving time under obstacle avoidance mode
const unsigned long DRIVE_DURATION_OBSTACLE_BACKWARD = 600; //milliseconds,the go backforward driving time under obstacle avoidance mode
const unsigned long DRIVE_DURATION_CMD_LEFT = 10; //milliseconds,the turn left driving time under command mode
const unsigned long DRIVE_DURATION_CMD_RIGHT = 10; //milliseconds,the turn right driving time under command mode
const unsigned long DRIVE_DURATION_CMD_FORWARD = 10; //milliseconds,the go forward driving time under command mode
const unsigned long DRIVE_DURATION_CMD_BACKWARD = 10; //milliseconds,the go backforward driving time under command mode
int driveMode;  //driving mode
int driveDirection; // driving direction
unsigned long driveDuration; //driving duration, milliseconds
unsigned long driveStartTime; //driving start time, milliseconds

//
//declare the ultrasonic sensor elements
//
//declare the min pulse LOW duration in millseconds (ms)
// suggested min pulse cycle time 60 ms
const unsigned long DURATION_PULSE_LOW = 60;
//declare the min pulse HIGH duration in microseconds (us)
// at least 10us
const unsigned long DURATION_PULSE_HIGH = 10;
//delcare the min safe distance in cm
const int SAFE_DISTANCE = 40; //cm, this should be larger than the TURN_DISTANCE
//delcare the min turn left/right distance in cm
const int TURN_DISTANCE = 15; //cm
//declare distance of obstacles
int cmFront;//the distance to the front obstacle in CM
int cmLeft;//the distance to the left obstacle in CM
int cmRight;//the distance to the right obstacle in CM
//declare the state of obstacle around
//3-bit unsigned number from B000 to B111
//constructed by result values the ultrasonic sensor detected
//according to the order: left, front,right
//1: obstacle is too close; 0: no obstacles or obstacle is at a safe distance;
byte obstacleState;

//
//declare the servo elements
//
// create servo object to control a servo
// twelve servo objects can be created on most boards
Servo myServo;
//the servo positions
const int POS_FRONT = 90; //front
const int POS_LEFT = 160; //left
const int POS_RIGHT = 10; //right
//the servo wait times in millseconds
const unsigned long TIME_SERVO_WAIT = 500;
const int SERVO_STEP = 1; //degree the servo step turns
const unsigned long TIME_SERVO_STEP = 10; //ms, wait time the servo step

//
//declare the buzzer elements
//
const int  BUZZER_FREQ = 4200; //Hz,frequency of the buzzer sound
const unsigned long  BUZZER_DURATION = 50; //ms,duration of the buzzer sound
int buzzerTimes;  //the buzzer alarm times

//
//declare the bluetooth elements
//
char cmd; //command
boolean hasCMD; //if there is a valid cmd
boolean isStopCMD;  //if CMD is stop
boolean isFreeCMD;  //if CMD is free
boolean isBackLightOn;  //if back lights on, also LCD backlight use this switch

//
//declare the LCD elements
//
char message[] = "Welcome! 2017"; //init welcome message

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600); //for program uploading and bluetooth communication

  //set LCD
  lcd.begin();
  isBackLightOn = true; //LCD backligh on
  lcdPrint(message);  //LCD display welcome msg

  //make the motor's pins output:
  pinMode(MOTORA_1_PIN, OUTPUT);
  pinMode(MOTORA_2_PIN, OUTPUT);
  pinMode(MOTORB_1_PIN, OUTPUT);
  pinMode(MOTORB_2_PIN, OUTPUT);

  // attaches pin to the servo object
  myServo.attach(SERVO_PIN);
  //servo turn to front
  servoInit();

  //set pin mode for HC-SR04 ultrasonic sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  //set pin mode for buzzer
  pinMode(BUZZER_PIN, OUTPUT);

  //set pins for led storbe
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);
}

void loop() {
  //  Serial.println("---------------------------------------");//TODO for test
  //Check if there is a valid Bluetooth command
  //updates:  cmd
  //updates:  hasCMD, isStopCMD, isFreeCMD, isBackLightOn
  checkCMD();
  Serial.print(cmd);//TODO for test
  Serial.print("  ");//TODO for test
  Serial.println(hasCMD);//TODO for test

  //turn on/off lcd backlight
  if (isBackLightOn) {
    lcdOn();
    //led storbe
    ledStorbe();
  } else {
    lcdOff();
  }

  //excute cmd
  if (hasCMD) { //valid CMD received
    //    lcdOff();  //LCD off
    if (isStopCMD) { //if CMD is STOP
      releaseCMD();
    } else if (isFreeCMD) { //if CMD is FREE
      buzzerTimes = 3; //set buzzer alarm times
      stopAndAutoCMD() ;
    } else {  // other CMD: F/B/L/R
      updateCMD() ;
    }
  } else { //no valid CMD
    if (driveMode == DRIVE_MODE_FREE) { //free mode
      //detect front obstacle and display on LCD
      cmFront = getDistance(); //delay method was used for ultrasonic sensor detecting
      lcdPrintFront();//LCD display front obstacle distance in 1st row

      //check if driving direction is stop
      if (driveDirection == DRIVE_DIRECTION_STOP) { //direction is stop
        //do nothing
      } else {  //direction is not stop
        //is there obstacle in front
        if (cmFront <= SAFE_DISTANCE) {//obstacles detected in front
          //          Serial.println("it is not safe, stop");//TODO for test
          buzzerTimes = 2; //set buzzer alarm times
          stopAndAutoCMD();
        } else { //no obstacles detected in front
          //do nothing
        }
      }
    } else {  // cmd or obstacle mode
      if (driveMode == DRIVE_MODE_OBSTACLE) { //obstacle mode
        if (millis() - driveStartTime >= driveDuration) {  //obstacle mode over time
          buzzerTimes = 1; //set buzzer alarm times
          stopAndAutoCMD();
        } else {  // under obstacle mode time
          //do nothing
        }
      } else {  //cmd mode
        releaseCMD();
      }
    }
  }

  //car runs according to the driveDirection value
  carRun(driveDirection);
}

//choose driving direction
//choose the best safe direction
//depends on: obstacleState
//depends on: cmFront,cmRight,cmLeft
//returns:  driveDirection value
int chooseDriveDirection() {
  switch (obstacleState) {
    case B000:  //obstacles: no; could choose any direction
      {
        //  if duration is valid in free mode, also could select left or right
        //        if (cmFront >= cmLeft && cmFront >= cmRight) {
        //          return DRIVE_DIRECTION_FORWARD; //go forward
        //        } else {
        //          return cmLeft >= cmRight ? DRIVE_DIRECTION_LEFT : DRIVE_DIRECTION_RIGHT;  //turn left/right
        //        }
        return DRIVE_DIRECTION_FORWARD; //go forward
      }
    case B001:   //obstacles: right; should turn left
      return DRIVE_DIRECTION_LEFT;  //turn left
    case B010: //obstacles: front; shoud turn left/right or go backward
      {
        if (cmFront >= TURN_DISTANCE) { //front has enough space to turn left/right
          return cmLeft >= cmRight ? DRIVE_DIRECTION_LEFT : DRIVE_DIRECTION_RIGHT; //turn left/right
        } else { //front has no enough space to turn left/right
          return DRIVE_DIRECTION_BACKWARD;  //go backward
        }
      }
    case B011: //obstacles: front,right; should go backward or turn left
      {
        if (cmFront >= TURN_DISTANCE && cmRight >= TURN_DISTANCE) { //front and right has enough space to turn left
          return DRIVE_DIRECTION_LEFT; //turn left
        } else { //front and right  has no enough space to turn left
          return DRIVE_DIRECTION_BACKWARD;  //go backward
        }
      }
    case B100: //obstacles: left; should turn right
      return DRIVE_DIRECTION_RIGHT;  //turn right
    case B101: //obstacles: left,right; should go forward
      return DRIVE_DIRECTION_FORWARD;  //go forward
    case B110: //obstacles: left,front; should go backward or turn right
      {
        if (cmFront >= TURN_DISTANCE && cmLeft >= TURN_DISTANCE) { //front and left has enough space to turn right
          return DRIVE_DIRECTION_RIGHT; //turn right
        } else { //front and left  has no enough space to turn right
          return DRIVE_DIRECTION_BACKWARD;  //go backward
        }
      }
    case B111: //obstacles: left,front,right; should go backward
      return DRIVE_DIRECTION_BACKWARD;  //go backward
    default:   // incorrect obstacleState, this should not happen under normal conditions
      return DRIVE_DIRECTION_STOP;  //stop
  }
}

//get drive duration according to the drive directon
//only for obstacle and cmd mode
//driveDirectionValue only accept: forward,backward,left,right
//invaild value will return 0
unsigned long getDuration(int driveModeValue, int driveDirectionValue) {
  if (driveModeValue == DRIVE_MODE_OBSTACLE) {
    switch (driveDirectionValue) {
      case DRIVE_DIRECTION_FORWARD:
        return DRIVE_DURATION_OBSTACLE_FORWARD;
      case DRIVE_DIRECTION_BACKWARD:
        return DRIVE_DURATION_OBSTACLE_BACKWARD;
      case DRIVE_DIRECTION_LEFT:
        return DRIVE_DURATION_OBSTACLE_LEFT;
      case DRIVE_DIRECTION_RIGHT:
        return DRIVE_DURATION_OBSTACLE_RIGHT;
      default : //incorrect driving direction
        return 0;
    }
  } else if (driveModeValue == DRIVE_MODE_CMD) {
    switch (driveDirectionValue) {
      case DRIVE_DIRECTION_FORWARD:
        return DRIVE_DURATION_CMD_FORWARD;
      case DRIVE_DIRECTION_BACKWARD:
        return DRIVE_DURATION_CMD_BACKWARD;
      case DRIVE_DIRECTION_LEFT:
        return DRIVE_DURATION_CMD_LEFT;
      case DRIVE_DIRECTION_RIGHT:
        return DRIVE_DURATION_CMD_RIGHT;
      default : //incorrect driving direction
        return 0;
    }
  }
  return 0;
}

//a free CMD or obstacls lead to
//stop the car and start to auto driving
//1:stop; 2:detect obstacles around; 3:set to auto run
//updates:  driveDirection (stop)
//updates:  cmFront,cmRight,cmLeft
//updates:  obstacleState
//update LCD distance message
//updates:  driveMode (FREE/OBSTACLE mode)
//updates:  driveDirection,driveDuration,driveStartTime
void stopAndAutoCMD() {
  //stop and detect obstacles around
  //
  driveDirection = DRIVE_DIRECTION_STOP;  //set direction to stop
  carRun(driveDirection);//car run

  //buzzer alarm according to the setting times
  //depends on: buzzerTimes
  //delay was user here
  buzzer();

  //servo turns around
  //ultrasonic sensor detects obstacls around
  //updates:  cmFront,cmRight,cmLeft
  updateAllDistance();

  //construct the obstacle state
  //according to the result values the ultrasonic sensor detected
  //depends on: cmFront,cmRight,cmLeft
  //updates:  obstacleState
  updateObstacleState();
  //LCD display front and sides obstacle distance
  lcdPrintAll();

  //set driving elements
  //
  driveMode = (obstacleState == B000 ? DRIVE_MODE_FREE : DRIVE_MODE_OBSTACLE);
  driveDirection = chooseDriveDirection();
  //there is no need to set driving duration in free mode
  driveDuration = getDuration(driveMode, driveDirection);
  driveStartTime = millis();
}

//a stop CMD or CMD over time leads to
//set driving mode to FREE and stop the car
//updates:  dirveMode
//updates:  driveDirection (there is no need to set stop duration)
//updates:  driveStartTime
void releaseCMD() {
  //set driving elements
  driveMode =  DRIVE_MODE_FREE;
  driveDirection = DRIVE_DIRECTION_STOP;
  //there is no need to set driving duration in free mode
  driveStartTime = millis();
}

//a non-stop CMD and non-free CMD leads to
//set driving mode to CMD and update the driving elements
//updates:  dirveMode
//updates:  driveDirection
//updates:  driveDuration
//updates:  driveStartTime
void updateCMD() {
  //set driving elements
  driveMode =  DRIVE_MODE_CMD;
  driveDirection = getCMDDirection();
  driveDuration = getDuration(driveMode, driveDirection);
  driveStartTime = millis();
}
