/**
  Bluetooth control car


  Motor Driver L298N-LITE


  Bluetooth HC-05
  Used pin:VCC,GND,TXD,RXD
  VCC: 3.6V-6V
  TXD:  UNO RXD
  RXD:  UNO TXD

  Eric
  2017-01-16  v1.0

*/


//
//delcare the arduino uno r3 pins
//
//declare motor pins
//from left to right
const int MOTORA_1_PIN = 4;   //LEFT 1: IN1
const int MOTORA_2_PIN = 5;   //LEFT 2: IN2
const int MOTORB_1_PIN = 6;  //RIGHT 1:  IN3
const int MOTORB_2_PIN = 7;  //RIGHT 2:  IN4
//declare bluetooth pins
//only use VCC,GND,TXD,RXD pins

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
//declare the bluetooth elements
//
char cmd; //command
boolean hasCMD; //if there is a valid cmd
boolean isStopCMD;  //if CMD is stop
boolean isFreeCMD;  //if CMD is free
boolean isBackLightOn;  //if back lights on, also LCD backlight use this switch

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600); //for program uploading and bluetooth communication

  //make the motor's pins output:
  pinMode(MOTORA_1_PIN, OUTPUT);
  pinMode(MOTORA_2_PIN, OUTPUT);
  pinMode(MOTORB_1_PIN, OUTPUT);
  pinMode(MOTORB_2_PIN, OUTPUT);
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
    //    lcdOn();
  } else {
    //    lcdOff();
  }

  //excute cmd
  if (hasCMD) { //valid CMD received
    //    lcdOff();  //LCD off
    if (isStopCMD) { //if CMD is STOP
      releaseCMD();
    } else if (isFreeCMD) { //if CMD is FREE
      releaseCMD();
      //      buzzerTimes = 3; //set buzzer alarm times
      //      stopAndAutoCMD() ;
    } else {  // other CMD: F/B/L/R
      updateCMD() ;
    }
  }

  //car runs according to the driveDirection value
  carRun(driveDirection);
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
