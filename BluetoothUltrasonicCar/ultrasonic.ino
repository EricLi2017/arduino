//ultrasonic sensor
//servo
//

//servo turn to front
void servoInit() {
  myServo.write(POS_FRONT); // tell servo to go to the position
}

//get the distance of the obstacles on the direction that ultrasonic sensor is facing
//note: floating point math is much slower than integer math in performing calculations
int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delay(DURATION_PULSE_LOW);//at least 60 ms
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(DURATION_PULSE_HIGH);//at least 10 us
  digitalWrite(TRIG_PIN, LOW);
  //  unsigned long pulseLength = pulseIn(ECHO_PIN, HIGH); //in microseconds (us)
  //  float cm =  pulseIn(ECHO_PIN, HIGH) / 58.0; //算成厘米 //直接就是保留两位小数了(除以58.0);如果是除以58，则后两位小数都是0.
  //  Serial.print(cm);//TODO for test
  //  Serial.print("  ");//TODO for test
  //  Serial.print(ceil(cm));//TODO for test
  //  Serial.print("  ");//TODO for test
  //  Serial.println(floor(cm));//TODO for test
  return floor(pulseIn(ECHO_PIN, HIGH) / 58.0);
}

//servo turns around
//ultrasonic sensor detects obstacls around
//depends on: myServo
//updates:  cmFront,cmRight,cmLeft
void updateAllDistance() {
  for (int pos = POS_FRONT; pos >= POS_RIGHT; pos -= SERVO_STEP) { // goes from front to right
    myServo.write(pos);              // tell servo to go to the position
    delay(TIME_SERVO_STEP);                       // waits for the servo to reach the position
  }
  cmRight = getDistance();

  //  myServo.write(POS_RIGHT);              // tell servo to go to the position
  //  delay(TIME_SERVO_WAIT);                       // waits for the servo to reach the position
  //  cmRight = getDistance();

  for (int pos = POS_RIGHT; pos <= POS_FRONT; pos += SERVO_STEP) { // goes from right to front
    myServo.write(pos);              // tell servo to go to the position
    delay(TIME_SERVO_STEP);                       // waits for the servo to reach the position
  }
  cmFront = getDistance();

  //  myServo.write(POS_FRONT);              // tell servo to go to the position
  //  delay(TIME_SERVO_WAIT);                       // waits for the servo to reach the position
  //  cmFront = getDistance();

  for (int pos = POS_FRONT; pos <= POS_LEFT; pos += SERVO_STEP) { // goes from front to left
    myServo.write(pos);              // tell servo to go to the position
    delay(TIME_SERVO_STEP);                       // waits for the servo to reach the position
  }
  cmLeft = getDistance();

  //  myServo.write(POS_LEFT);              // tell servo to go to the position
  //  delay(TIME_SERVO_WAIT);                       // waits for the servo to reach the position
  //  cmLeft = getDistance();

  for (int pos = POS_LEFT; pos >= POS_FRONT; pos -= SERVO_STEP) { // goes from left to front
    myServo.write(pos);              // tell servo to go to the position
    delay(TIME_SERVO_STEP);                       // waits for the servo to reach the position
  }
  //  cmFront = getDistance();

  //  myServo.write(POS_FRONT);              // tell servo to go to the position
  //  delay(TIME_SERVO_WAIT);                       // waits for the servo to reach the position
  ////    cmFront = getDistance();
}

//construct the obstacle state
//according to the result values the ultrasonic sensor detected
//depends on: cmFront,cmRight,cmLeft
//updates:  obstacleState
void updateObstacleState() {
  //left obstacle
  if (cmLeft <= SAFE_DISTANCE) { //obstacle is too close
    obstacleState = obstacleState | B100;
  } else { //no obstacles or obstacle is in a safe distance
    obstacleState = obstacleState & B011;
  }

  //front obstacle
  if (cmFront <= SAFE_DISTANCE) { //obstacle is too close
    obstacleState = obstacleState | B010;
  } else { //no obstacles or obstacle is in a safe distance
    obstacleState = obstacleState & B101;
  }

  //right obstacle
  if (cmRight <= SAFE_DISTANCE) { //obstacle is too close
    obstacleState = obstacleState | B001;
  } else { //no obstacles or obstacle is in a safe distance
    obstacleState = obstacleState & B110;
  }
}
