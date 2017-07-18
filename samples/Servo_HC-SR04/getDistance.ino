//declare the min pulse LOW duration in millseconds (ms)
// suggested min pulse cycle time 60 ms
const unsigned long DURATION_PULSE_LOW = 60;
//declare the min pulse HIGH duration in microseconds (us)
// at least 10us
const unsigned long DURATION_PULSE_HIGH = 10;

float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delay(DURATION_PULSE_LOW);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(DURATION_PULSE_HIGH);//us
  digitalWrite(TRIG_PIN, LOW);

  //unsigned long pulseLength;//in microseconds (us)
  //  pulseLength = pulseIn(ECHO_PIN, HIGH);//读取返回的高电平持续时间
  //  cm =  pulseIn(ECHO_PIN, HIGH) / 58.0; //算成厘米 //直接就是保留两位小数了(除以58.0);如果是除以58，则后两位小数都是0.

  return pulseIn(ECHO_PIN, HIGH) / 58.0;
}

//updates:cmRight
//updates:cmLeft
void updateBothSidesDistance() {
  myServo.write(POS_RIGHT);              // tell servo to go to the position
  delay(TIME_SERVO_WAIT);                       // waits for the servo to reach the position
  cmRight = getDistance();

  myServo.write(POS_FRONT);              // tell servo to go to the position
  delay(TIME_SERVO_WAIT);                       // waits for the servo to reach the position
  //  cmFront = getDistance();

  myServo.write(POS_LEFT);              // tell servo to go to the position
  delay(TIME_SERVO_WAIT);                       // waits for the servo to reach the position
  cmLeft = getDistance();

  myServo.write(POS_FRONT);              // tell servo to go to the position
  delay(TIME_SERVO_WAIT);                       // waits for the servo to reach the position
  //  cmFront = getDistance();
}
