//wheels
//

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

//run according to the driveDirection
void carRun(int driveDirectionValue) {
  switch (driveDirectionValue) {
    case DRIVE_DIRECTION_FORWARD:
      {
        goForward();
      }
      break;
    case DRIVE_DIRECTION_BACKWARD:
      {
        goBackward();
      }
      break;
    case DRIVE_DIRECTION_LEFT:
      {
        turnLeft();
      }
      break;
    case DRIVE_DIRECTION_RIGHT:
      {
        turnRight();
      }
      break;
    case DRIVE_DIRECTION_STOP:
      {
        park();
      }
      break;
    default : //incorrect driving direction
      //      Serial.println("  incorrect driving direction");
      break; //do nothing;
  }
}
