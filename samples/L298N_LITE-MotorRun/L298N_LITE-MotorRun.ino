/*
   A L298N motor run test
*/


//declare motor pins
//from left to right
const int MOTORA_1_PIN = 4;   //LEFT 1: IN1
const int MOTORA_2_PIN = 5;   //LEFT 2: IN2
const int MOTORB_1_PIN = 6;  //RIGHT 1:  IN3
const int MOTORB_2_PIN = 7;  //RIGHT 2:  IN4


//left wheel forward
void leftWheelForward() {
  //TODO
  digitalWrite(MOTORA_1_PIN, HIGH);
  digitalWrite(MOTORA_2_PIN, LOW);
}
//right wheel forward
void rightWheelForward() {
  //TODO
  digitalWrite(MOTORB_1_PIN, HIGH);
  digitalWrite(MOTORB_2_PIN, LOW);
}
//left wheel backward
void leftWheelBackward() {
  //TODO
  digitalWrite(MOTORA_1_PIN, LOW);
  digitalWrite(MOTORA_2_PIN, HIGH);
}
//right wheel backward
void rightWheelBackward() {
  //TODO
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

void setup() {
  // put your setup code here, to run once:
  //make the motor's pins output:
  pinMode(MOTORA_1_PIN, OUTPUT);
  pinMode(MOTORA_2_PIN, OUTPUT);
  pinMode(MOTORB_1_PIN, OUTPUT);
  pinMode(MOTORB_2_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //two wheels bothStop for a while
  //  bothStop();
  //  delay(1000);

  //two wheels forward for a while
  //  pinMode(MOTOR_IN4_PIN,OUTPUT);
  //  pinMode(MOTOR_IN3_PIN,OUTPUT);
  //  pinMode(MOTOR_IN2_PIN,OUTPUT);
  //  pinMode(MOTOR_IN1_PIN,OUTPUT);
//  leftWheelForward();
  //  rightWheelForward();
  //  delay(2000);

  //two wheels bothStop for a while
  //  bothStop();
  //  delay(2000);

  //two wheels backward for a while
  //  leftWheelBackward();
  //  rightWheelBackward();
  //  delay(2000);
  //
  //  //two wheels bothStop for a while
  //  bothStop();
  //  delay(2000);

      goForward();
      delay(2000);
  //  park();
  //  delay(2000);
    goBackward();
    delay(2000);
  //  park();
  //  delay(2000);
  //  turnLeft();
  //  delay(2000);
  //  park();
  //  delay(2000);
  //  turnRight();
  //  delay(2000);
  //  park();
  //  delay(2000);

  //  analogWrite(MOTORB_2_PIN, 255);
  //  digitalWrite(MOTORB_1_PIN, LOW);

}




