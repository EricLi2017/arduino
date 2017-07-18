/*
   A L298N motor run test
*/


//declare motor pins
//from left to right
const int MOTORA_1_PIN = 8;   //LEFT 1: IN1
const int MOTORA_2_PIN = 9;   //LEFT 2: IN2
const int MOTORA_ENA_PIN = 10;   //LEFT PWM: ENA
const int MOTORB_1_PIN = 12;  //RIGHT 1:  IN3
const int MOTORB_2_PIN = 13;  //RIGHT 2:  IN4
const int MOTORB_ENB_PIN = 11;  //RIGHT PWM:  ENB


//left wheel forward
void leftWheelForward() {
  digitalWrite(MOTORA_1_PIN, LOW);
  digitalWrite(MOTORA_2_PIN, HIGH);
}
//right wheel forward
void rightWheelForward() {
  digitalWrite(MOTORB_1_PIN, LOW);
  digitalWrite(MOTORB_2_PIN, HIGH);
}
//left wheel backward
void leftWheelBackward() {
  digitalWrite(MOTORA_1_PIN, HIGH);
  digitalWrite(MOTORA_2_PIN, LOW);
}
//right wheel backward
void rightWheelBackward() {
  digitalWrite(MOTORB_1_PIN, HIGH);
  digitalWrite(MOTORB_2_PIN, LOW);
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
  pinMode(MOTORA_ENA_PIN, OUTPUT);
  pinMode(MOTORB_1_PIN, OUTPUT);
  pinMode(MOTORB_2_PIN, OUTPUT);
  pinMode(MOTORB_ENB_PIN, OUTPUT);

  //  digitalWrite(MOTORA_1_PIN, LOW);
  //  digitalWrite(MOTORA_2_PIN, HIGH);
  //  analogWrite(MOTORA_ENA_PIN, 255);
}

void loop() {
  //  goForward();
  //  delay(2000);
  //  park();
  //  delay(2000);
  //  goBackward();
  //  delay(2000);
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

  //  for (int i = 0; i <= 255; i++) {
  //    digitalWrite(MOTORA_1_PIN, LOW);
  //    digitalWrite(MOTORA_2_PIN, HIGH);
  //    analogWrite(MOTORA_ENA_PIN, i);
  //    delay(50);
  //  }
  //  for (int i = 255; i >= 0; i--) {
  //    digitalWrite(MOTORA_1_PIN, HIGH);
  //    digitalWrite(MOTORA_2_PIN, LOW);
  //    analogWrite(MOTORA_ENA_PIN, i);
  //    delay(50);
  //  }
  //  for (int i = 100; i <= 0; i--) {
  //    digitalWrite(MOTORB_1_PIN, HIGH);
  //    digitalWrite(MOTORB_2_PIN, LOW);
  //    analogWrite(MOTORB_ENB_PIN, i);
  //    delay(500);
  //  }

  digitalWrite(MOTORA_1_PIN, HIGH);
  digitalWrite(MOTORA_2_PIN, LOW);
  analogWrite(MOTORA_ENA_PIN, 255);
  //  delay(1000);
  //
  //  digitalWrite(MOTORB_1_PIN, HIGH);
  //  digitalWrite(MOTORB_2_PIN, LOW);
  //  analogWrite(MOTORB_ENB_PIN, 255);

}




