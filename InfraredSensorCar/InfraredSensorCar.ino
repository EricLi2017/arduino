/*
  Arduino Car
  Features: An auto-pilot obstacle avoidance car

  Include 3 main electronic modules: arduino uno r3 board, motor drive board, infrared sensor.
  Include 2 power sources: 5V*1 for motor drive board, 5V*1 for auduino uno r3

  arduino uno r3 board
  5V board, refer arduino.cc for details

  电机驱动模块
  主控芯片：L298N
  驱动电压：5V-35V
  驱动电流：2A(MAX单桥)
  最大功率：25W
  逻辑电压：5V
  逻辑电流：0mA-36mA
  外部接口：VCC,GND,IN1,IN2,IN3,IN4,OUT1,OUT2,OUT3,OUT4
  其中，VCC和GND是电源接口，GND要注意和arduino uno r3的GND连接（共地）；IN1-IN4分别对应OUT1-OUT4。
  连接方式：VCC和GND分别连接独立电源的正负极，并且GND与arduino uno r3的GND连接（共地）；
  IN1-IN4分别接arduino uno r3的4个digital I/O接口；
  OUT1+OUT2与OUT3+OUT4分别接到两个电机马达。

  红外传感器模块
  工作电压：DC 3.3V-5V
  外部接口：VCC,GND,IN1,IN2,IN3,IN4
  连接方式：VCC和GND分别接arduino uno r3的+5V和GND，IN1-IN4分别接arduino uno r3的4个digital I/O接口
  工作模式：共有四个红外探头IN1,IN2,IN3,IN4。对于每个探头来说：
  如果前面没有障碍物或者障碍物反射红外线能力不强（比如黑色物体)就返回HIGH（就是波没反射回来或者反射回来的波不够多）；
  如果前面有障碍物并且障碍物反射红外线能力很强（比如白色物体）就返回LOW（就是反射回来的波足够多）。

  自动驾驶原则：有障避障，无障闲逛。
  障碍物情况优先级高于驾驶模式：根据当前障碍物得到的行驶方向和行驶时间更新驾驶模式
  避障模式优先级高于闲逛模式：进入闲逛模式之前要运行完避障模式下设定的行驶方向和行驶时间
  行驶要素：行驶模式，行驶方向，行驶时间。
  有障避障：左边有障就右转，右边有障就左转，前面有障就后退。
  无障闲逛：随机选择方向和时间，闲逛直到遇到障碍物。
  障碍物情况优先级高于驾驶模式：根据当前障碍物得到的行驶方向和行驶时间更新驾驶模式
  避障模式优先级高于闲逛模式：进入闲逛模式之前要运行完避障模式下设定的行驶方向和行驶时间
  根据IN1-IN4四个红外探头是否探测到障碍物来决定小车运动方向：
  1代表这个探头探测到障碍物，0代表这个探头没有探测到障碍物。

  12/12/2016
  Eric
*/

//declare infrared sensor pins
//order: left,front,right,back
const int INFRARED_F_PIN = 9; //front infrared sensor :  IN2
const int INFRARED_B_PIN = 10; //back infrared sensor :  IN3
const int INFRARED_L_PIN = 11; //left infrared sensor :  IN4
const int INFRARED_R_PIN = 8; //right infrared sensor :  IN1

//declare motor pins
//from left to right
const int MOTORA_1_PIN = 4;   //LEFT 1: IN1
const int MOTORA_2_PIN = 5;   //LEFT 2: IN2
const int MOTORB_1_PIN = 6;  //RIGHT 1:  IN3
const int MOTORB_2_PIN = 7;  //RIGHT 2:  IN4

//delcare buzzer pin
const int BUZZER_PIN = 2;

//declare driving elements
//the const driving elements
const int DRIVE_MODE_FREE = 0;          //free driving mode
const int DRIVE_MODE_OBSTACLE = 1;      //obstacle avoidance mode
const int DRIVE_DIRECTION_FORWARD = 1;  //go forward
const int DRIVE_DIRECTION_BACKWARD = 2; //go backward
const int DRIVE_DIRECTION_LEFT = 3;     //turn left
const int DRIVE_DIRECTION_RIGHT = 4;    //turn right
const int DRIVE_DIRECTION_STOP = 5;     //stay in place /stop
const unsigned long DRIVE_DURATION_OBSTACLE_LEFT = 800; //milliseconds,the turn left driving time under obstacle avoidance mode
const unsigned long DRIVE_DURATION_OBSTACLE_RIGHT = 800; //milliseconds,the turn right driving time under obstacle avoidance mode
const unsigned long DRIVE_DURATION_OBSTACLE_FORWARD = 2000; //milliseconds,the go forward driving time under obstacle avoidance mode
const unsigned long DRIVE_DURATION_OBSTACLE_BACKWARD = 1500; //milliseconds,the go backforward driving time under obstacle avoidance mode
const unsigned long MIN_DRIVE_DURATION_FREE = 1000; //milliseconds,the MIN driving time to any directions under free driving mode
const unsigned long MAX_DRIVE_DURATION_FREE = 5000; //milliseconds,the MAX driving time to any directions under free driving mode
const unsigned long BUZZER_DURATION = 400; //milliseconds,duration of the buzzer
const unsigned long BUZZER_SOUND_DURATION = 50; //milliseconds,duration of the buzzer make sound
const int  BUZZER_FREQ = 2000; //Hz,frequency of the buzzer sound

//driving elements
int driveMode;
int driveDirection;
unsigned long driveDuration; //milliseconds

//driving start time
unsigned long driveStartTime; //milliseconds
//the buzzer start time
unsigned long buzzerStartTime; //milliseconds

//the time of now
unsigned long now;


//the state of obstacle around
//4-bit unsigned number from B0000 to B1111
//constructed by result values on the infrared sensor
//according to the order: INFRARED_F_PIN,INFRARED_B_PIN,INFRARED_L_PIN,INFRARED_R_PIN
//1: obstacles detected; 0: no obstacles dectected;
byte obstacleState;

//infrared sensor detect obstacle
//updates: obstacleState
void infraredSensorDetect();
//auto drive car according to the detection results of the sensors
//depends on: obstacleState
//depends on: driveMode,driveDirection,driveDuration
//updates: now
//updates: driveMode,driveDirection,driveDuration
void carAutoDrive();

// put your setup code here, to run once:
void setup() {
  // initialize serial communication at 9600 bits per second:
  //  Serial.begin(9600);//TODO for test

  // make the sensor's pins input:
  pinMode(INFRARED_L_PIN, INPUT);
  pinMode(INFRARED_B_PIN, INPUT);
  pinMode(INFRARED_F_PIN, INPUT);
  pinMode(INFRARED_R_PIN, INPUT);

  //make the motor's pins output:
  pinMode(MOTORA_1_PIN, OUTPUT);
  pinMode(MOTORA_2_PIN, OUTPUT);
  pinMode(MOTORB_1_PIN, OUTPUT);
  pinMode(MOTORB_2_PIN, OUTPUT);

  // if analog input pin A0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(A0));

  //initialize the now time
  now = millis();
  //initialize the infrared sensor
  obstacleState = B0000;

  //initialize the driving
  driveMode = DRIVE_MODE_FREE;
  driveDirection = DRIVE_DIRECTION_STOP;
  driveDuration = 0;
  driveStartTime = now;
}

// put your main code here, to run repeatedly:
void loop() {
  //infrared sensor detect obstacle
  infraredSensorDetect();
  //auto drive car according to the detection results of the sensors
  carAutoDrive();
}

//infrared sensor detect obstacle
//updates: obstacleState
void infraredSensorDetect() {
  //front infrared sensor
  if (LOW == digitalRead(INFRARED_F_PIN)) { //obstacles detected
    obstacleState = obstacleState | B1000;
  } else { //no obstacles detected
    obstacleState = obstacleState & B0111;
  }

  //back infrared sensor
  if (LOW == digitalRead(INFRARED_B_PIN)) { //obstacles detected
    obstacleState = obstacleState | B0100;
  } else { //no obstacles detected
    obstacleState = obstacleState & B1011;
  }

  //left infrared sensor
  if (LOW == digitalRead(INFRARED_L_PIN)) { //obstacles detected
    obstacleState = obstacleState | B0010;
  } else { ////no obstacles detected
    obstacleState = obstacleState & B1101;
  }

  //right infrared sensor
  if (LOW == digitalRead(INFRARED_R_PIN)) { //obstacles detected
    obstacleState = obstacleState | B0001;
  } else { //no obstacles detected
    obstacleState = obstacleState & B1110;
  }
}

//left wheel forward
void leftWheelForward() {
  digitalWrite(MOTORA_1_PIN, HIGH);
  digitalWrite(MOTORA_2_PIN, LOW);
}
//right wheel forward
void rightWheelForward() {
  digitalWrite(MOTORB_1_PIN, HIGH);
  digitalWrite(MOTORB_2_PIN, LOW);
}
//left wheel backward
void leftWheelBackward() {
  digitalWrite(MOTORA_1_PIN, LOW);
  digitalWrite(MOTORA_2_PIN, HIGH);
}
//right wheel backward
void rightWheelBackward() {
  digitalWrite(MOTORB_1_PIN, LOW);
  digitalWrite(MOTORB_2_PIN, HIGH);
}
//left wheel stop
void leftWheelStop() {
  digitalWrite(MOTORA_1_PIN, LOW);
  digitalWrite(MOTORA_2_PIN, LOW);
}
//right wheel stop
void rightWheelStop() {
  digitalWrite(MOTORB_1_PIN, LOW);
  digitalWrite(MOTORB_2_PIN, LOW);
}

//car turn left
void turnLeft() {
  leftWheelStop();
  rightWheelForward();
}
//car turn right
void turnRight() {
  leftWheelForward();
  rightWheelStop();
}
//car go forward
void goForward() {
  leftWheelForward();
  rightWheelForward();
}
//car go backward
void goBackward() {
  leftWheelBackward();
  rightWheelBackward();
}
//car stop
void park() {
  leftWheelStop();
  rightWheelStop();
}

//run according to the driveDirection
//depends on: driveDirection
void carRun() {
  //TODO for test
  //  Serial.print(now);
  //  Serial.print("  ");
  //  Serial.print("  obstacleState:");
  //  Serial.print(obstacleState);
  //  Serial.print("  driveMode:");
  //  Serial.print(driveMode);
  //  Serial.print("  driveDirection:");
  //  Serial.print(driveDirection);
  //  Serial.print("  driveDuration:");
  //  Serial.print(driveDuration);
  switch (driveDirection) {
    case DRIVE_DIRECTION_FORWARD:
      {
        //        Serial.println("  go forward");//TODO for test
        goForward();
      }
      break;
    case DRIVE_DIRECTION_BACKWARD:
      {
        //        Serial.println("  go backward");//TODO for test
        goBackward();
      }
      break;
    case DRIVE_DIRECTION_LEFT:
      {
        //        Serial.println("  turn left");//TODO for test
        turnLeft();
      }
      break;
    case DRIVE_DIRECTION_RIGHT:
      {
        //        Serial.println("  turn right");//TODO for test
        turnRight();
      }
      break;
    case DRIVE_DIRECTION_STOP:
      {
        //        Serial.println("  stop");//TODO for test
        park();
      }
      break;
    default : //incorrect driving direction
      //      Serial.println("  incorrect driving direction");
      break; //do nothing;
  }
}

//random choose a driving direction
int randomDriveDirection() {
  //return a random driving direction from DRIVE_DIRECTION_FORWARD to DRIVE_DIRECTION_STOP
  return (int) random(DRIVE_DIRECTION_FORWARD, DRIVE_DIRECTION_STOP + 1);
}
//random choose a driving duration
unsigned long randomDriveDuration() {
  //return a random driving duration from MIN_DRIVE_DURATION_FREE to MAX_DRIVE_DURATION_FREE
  return random(MIN_DRIVE_DURATION_FREE, MAX_DRIVE_DURATION_FREE + 1);
}

//choose a driving direction based on the obstacleStateValue
int chooseDriveDirection(byte obstacleStateValue) {
  switch (obstacleStateValue) {
    case B0000:	//obstacles: no; could choose any direction
      return randomDriveDirection();
    case B0001: 	//obstacles: right; should turn left
      return DRIVE_DIRECTION_LEFT;
    case B0010: //obstacles: left; shoud turn right
      return DRIVE_DIRECTION_RIGHT;
    case B0011: //obstacles: left,right; should go forward
      return DRIVE_DIRECTION_FORWARD;
    case B0100: //obstacles: back; should go forward
      return DRIVE_DIRECTION_FORWARD;
    case B0101: //obstacles: back,right; should turn left
      return DRIVE_DIRECTION_LEFT;
    case B0110: //obstacles: back,left; should turn right
      return DRIVE_DIRECTION_RIGHT;
    case B0111: //obstacles: back,left,right; should go forward
      return DRIVE_DIRECTION_FORWARD;
    case B1000: //obstacles: front; should go backward
      return DRIVE_DIRECTION_BACKWARD;
    case B1001: //obstacles: front,right; should go backward
      return DRIVE_DIRECTION_BACKWARD;
    case B1010: //obstacles: front,left; should go backward
      return DRIVE_DIRECTION_BACKWARD;
    case B1011: //obstacles: front,left,right; should go backward
      return DRIVE_DIRECTION_BACKWARD;
    case B1100: //obstacles: front,back; should stop
      return DRIVE_DIRECTION_STOP;
    case B1101: //obstacles: front,back,right; should stop
      return DRIVE_DIRECTION_STOP;
    case B1110: //obstacles: front,back,left; should stop
      return DRIVE_DIRECTION_STOP;
    case B1111: //obstacles: back; should go forward
      return DRIVE_DIRECTION_STOP;
    default:   // incorrect obstacleState, this should not happen under normal conditions
      return DRIVE_DIRECTION_STOP; // stop
  }
}
//choose a driving duration based on the driveMode and driveDirectionValue
//depends on: driveMode
unsigned long chooseDriveDuration(int driveDirectionValue) {
  //not in the obstacle avoidance mode
  if (!(driveMode == DRIVE_MODE_OBSTACLE)) {
    return randomDriveDuration();
  }

  //in the obstacle avoidance mode
  switch (driveDirectionValue) {
    case DRIVE_DIRECTION_FORWARD:
      return DRIVE_DURATION_OBSTACLE_FORWARD;
    case DRIVE_DIRECTION_BACKWARD:
      return DRIVE_DURATION_OBSTACLE_BACKWARD;
    case DRIVE_DIRECTION_LEFT:
      return DRIVE_DURATION_OBSTACLE_LEFT;
    case DRIVE_DIRECTION_RIGHT:
      return DRIVE_DURATION_OBSTACLE_RIGHT;
    default:  // incorrect driveDirectionValue, this should not happen under normal conditions
      return DRIVE_DURATION_OBSTACLE_FORWARD;
  }
}

//buzzer
//depends on: driveMode
//updates: buzzerStartTime
void buzzer() {
  if (driveMode == DRIVE_MODE_OBSTACLE) {
    if (millis() - buzzerStartTime >= BUZZER_DURATION) {
      buzzerStartTime = millis();
      tone (BUZZER_PIN, BUZZER_FREQ);//sound
    } else if (millis() - buzzerStartTime <= BUZZER_SOUND_DURATION) {
      tone (BUZZER_PIN, BUZZER_FREQ);//sound
    } else {
      noTone (BUZZER_PIN); //no sound
    }
  } else {
    noTone (BUZZER_PIN); //no sound
  }
}

//reset the driving based on the obstacleState
//depends on: obstacleState
//updates:driveStartTime
//updates:driveDirection,driveDuration
void drivingReset() {
  driveStartTime = millis();				//reset the driving start time
  driveDirection = chooseDriveDirection(obstacleState);//reset the driving direction (choose based on the obstacleState)
  driveDuration = chooseDriveDuration(driveDirection);	//reset the driving duration (choose based on the driveMode and driveDirectionValue)
}

//auto drive car according to the detection results of the sensors
//depends on: obstacleState
//depends on: driveMode,driveDirection,driveDuration
//updates: now
//updates: driveMode,driveDirection,driveDuration
void carAutoDrive() {
  //updates now time
  now = millis();

  //no any obstacles detected
  if (obstacleState == B0000) {
    if (driveMode == DRIVE_MODE_FREE) {
      if (now - driveStartTime >= driveDuration) {//free driving over time
        park();//stop first for changing driving direction

        drivingReset();	//reset the driving based on the obstacleState
      } else { //free driving continue
        //do nothing
      }
    } else {
      if (now - driveStartTime >= driveDuration) { //obstacle avoidance driving over time
        driveMode = DRIVE_MODE_FREE;			// change the drive mode

        drivingReset();	//reset the driving based on the obstacleState
      } else {	//obstacle avoidance driving continue
        //do nothing
      }
    }
  } else {		//some obstacles detected
    if (driveMode != DRIVE_MODE_OBSTACLE) {
      driveMode = DRIVE_MODE_OBSTACLE;      // change the drive mode

      park();//stop first for changing driving direction
    }
    drivingReset();    //reset the driving based on the obstacleState
  }


  //buzzer according to the driveMode
  buzzer();

  //run according to the driveDirection
  carRun();
}
