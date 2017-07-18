/*
   Arduino Car

   Include 3 main electronic modules: arduino uno r3 board, motor drive board, infrared sensor.

   Features: Black line tracking car

   电机驱动模块//TODO
   工作电压：DC 2V-10V
   外部接口：VCC,GND,IN1,IN2,IN3,IN4,motor a1,motor a2,motor b1,motor b2
             其中，VCC和GND是电源接口，GND要注意和arduino uno r3的GND连接（共地）；IN1,IN2控制motor a,IN3,IN4控制motor b。
   连接方式：????//TODO

   红外传感器模块
   工作电压：DC 3.3V-5V
   外部接口：VCC,GND,IN1,IN2,IN3,IN4
   连接方式：VCC和GND分别接arduino uno r3的+5V和GND，IN1-IN4分别接arduino uno r3的4个digital I/O接口
   共有四个红外探头IN1,IN2,IN3,IN4。对于每个探头来说：
   如果前面没有任何遮挡或者检测到黑线就返回HIGH（就是有些波没被反射回来）；
   如果前面有东西遮挡并且没有检测到黑线就返回LOW（就是波都被反射回来了）。

   12/18/2016
   Eric
*/
//declare infrared sensor pins
const int INFRARED_IN1_PIN = 4; //红外探头IN1
const int INFRARED_IN2_PIN = 5; //红外探头IN2
const int INFRARED_IN3_PIN = 6; //红外探头IN3
const int INFRARED_IN4_PIN = 7; //红外探头IN4

//declare motor pins
const int MOTORA_1_PIN = 8;
const int MOTORA_2_PIN = 9;
const int MOTORB_1_PIN = 10;
const int MOTORB_2_PIN = 11;

//whether a black line is detected by the infrarared sensor
//true: a black line is detected; false: a black line is not detected
boolean is1; //left sensor
boolean is2; //left-middle sensor
boolean is3; //right-middle sensor
boolean is4; //right sensor

//infrared sensor detect black line
//updates: is1,is2,is3,is4
void infraredSensorDetect();
//motor drive car wheels according to the detection results of the sensors
//depends on: is1,is2,is3,is4
void carAutoDrive();

// put your setup code here, to run once:
void setup() {
  // make the sensor's pins input:
  pinMode(INFRARED_IN1_PIN, INPUT);
  pinMode(INFRARED_IN2_PIN, INPUT);
  pinMode(INFRARED_IN3_PIN, INPUT);
  pinMode(INFRARED_IN4_PIN, INPUT);

  //make the motor's pins output:
  pinMode(MOTORA_1_PIN, OUTPUT);
  pinMode(MOTORA_2_PIN, OUTPUT);
  pinMode(MOTORB_1_PIN, OUTPUT);
  pinMode(MOTORB_2_PIN, OUTPUT);
}

// put your main code here, to run repeatedly:
void loop() {
  //infrared sensor detect black line
  infraredSensorDetect();
  //motor drive car wheels according to the detection results of the sensors
  carAutoDrive();
}

//infrared sensor detect black line
//updates: is1,is2,is3,is4
void infraredSensorDetect() {
  //infrared sensor 1
  if (HIGH == digitalRead(INFRARED_IN1_PIN)) {
    is1 = true;
  } else {
    is1 = false;
  }
  //infrared sensor 2
  if (HIGH == digitalRead(INFRARED_IN2_PIN)) {
    is2 = true;
  } else {
    is2 = false;
  }
  //infrared sensor 3
  if (HIGH == digitalRead(INFRARED_IN3_PIN)) {
    is3 = true;
  } else {
    is3 = false;
  }
  //infrared sensor 4
  if (HIGH == digitalRead(INFRARED_IN4_PIN)) {
    is4 = true;
  } else {
    is4 = false;
  }
}

//left wheel forward
void leftForward() {
  //TODO
  digitalWrite(MOTORA_1_PIN, LOW);
  digitalWrite(MOTORA_2_PIN, HIGH);
}

//right wheel forward
void rightForward() {
  //TODO
  digitalWrite(MOTORB_1_PIN, LOW);
  digitalWrite(MOTORB_2_PIN, HIGH);
}

//left wheel backward
void leftBackward() {
  digitalWrite(MOTORA_1_PIN, HIGH);
  digitalWrite(MOTORA_2_PIN, LOW);
}

//right wheel backward
void rightBackward() {
  //TODO
  digitalWrite(MOTORB_1_PIN, HIGH);
  digitalWrite(MOTORB_2_PIN, LOW);
}
//left wheel stop
void leftStop() {
  //TODO
  digitalWrite(MOTORA_1_PIN, LOW);
  digitalWrite(MOTORA_2_PIN, LOW);
}

//right wheel stop
void rightStop() {
  //TODO
  digitalWrite(MOTORB_1_PIN, LOW);
  digitalWrite(MOTORB_2_PIN, LOW);
}

//two wheels stop
void bothStop() {
  leftStop();
  rightStop();
}

//car turn left
void turnLeft() {
  leftStop();
  rightForward();
}
//car turn right
void turnRight() {
  leftForward();
  rightStop();
}
//car go forward
void goForward() {
  leftForward();
  rightForward();
}
//car stop
void park() {
  bothStop();
}

//motor drive car wheels according to the detection results of the sensors
//depends on: is1,is2,is3,is4
void carAutoDrive() {
  //根据IN1-IN4四个红外探头的返回值决定小车运动方向：1代表这个探头探测到黑线，0代表这个探头没有探测到黑线，x代表不管这个探头有没有探测到黑线
  //turn left:  1xx0
  if (is1 && !is4) {
    turnLeft();
  }
  //turn right:  0xx1
  if (!is1 && is4) {
    turnRight();
  }
  //go forward:  01x0, 0x10
  if ((!is1 && !is4) && (is3 || is4))
  {
    goForward();
  }
  //stop:     1xx1
  if (is1 && is4) {
    park();
  }
}


